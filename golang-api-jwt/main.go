package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"strings"

	"database/sql"

	"github.com/davecgh/go-spew/spew"
	"github.com/dgrijalva/jwt-go"
	"github.com/gorilla/mux"
	_ "github.com/mattn/go-sqlite3"
	"golang.org/x/crypto/bcrypt"
)

var db *sql.DB

func setupDB(db *sql.DB) {
	script := `
	CREATE TABLE IF NOT EXISTS "users" (
		"id"	INTEGER PRIMARY KEY AUTOINCREMENT,
		"email"	TEXT NOT NULL UNIQUE,
		"password"	TEXT NOT NULL
	);
	

  `
	stmt, err := db.Prepare(script)
	if err != nil {
		log.Fatal(err.Error())
	}
	stmt.Exec()
}

// User ...
type User struct {
	ID       int    `json:"id"`
	Email    string `json:"email"`
	Password string `json:"password"`
}

// JWT ...
type JWT struct {
	Token string `json:"token"`
}

// Error ..
type Error struct {
	Message string `json:"message"`
}

func main() {
	db, err := sql.Open("sqlite3", "./data.db")
	if err != nil {
		log.Fatal("could not open the data")
	}

	setupDB(db)

	router := mux.NewRouter()

	router.HandleFunc("/signup", signup).Methods("POST")
	router.HandleFunc("/login", login).Methods("POST")
	router.HandleFunc("/protected", tokenVerifyMiddleware(protected)).Methods("GET")

	log.Println("Listenning on port 8000")
	err = http.ListenAndServe(":8000", router)
	if err != nil {
		log.Fatal(err)
	}

}

func respondWithError(w http.ResponseWriter, status int, err Error) {
	w.WriteHeader(status)
	json.NewEncoder(w).Encode(err)
}

func respondWithData(w http.ResponseWriter, data interface{}) {
	json.NewEncoder(w).Encode(data)
}

func signup(w http.ResponseWriter, r *http.Request) {
	var user User
	var error Error

	json.NewDecoder(r.Body).Decode(&user)
	if user.Email == "" || user.Password == "" {
		error.Message = "invalid data submited"
		respondWithError(w, http.StatusBadRequest, error)
		return
	}

	hash, err := bcrypt.GenerateFromPassword([]byte(user.Password), 10)
	if err != nil {
		log.Fatal(err)
	}

	user.Password = string(hash)
	stmt := "INSERT INTO users(email, password) VALUES($1, $2);"

	err = db.QueryRow(stmt, user.Email, user.Password).Scan(&user.ID)
	if err != nil {
		error.Message = "Server error"
		respondWithError(w, http.StatusBadRequest, error)
		return
	}

	user.Password = ""
	w.Header().Set("Content-Type", "application/json")
	respondWithData(w, user)

	log.Println("User was created!")
	spew.Dump(user)
}

func GenerateToken(user User) (string, error) {
	var err error
	secret := "scretet"

	token := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
		"email": user.Email,
		"iss":   "course",
	})

	tokenString, err := token.SignedString([]byte(secret))
	if err != nil {
		log.Fatal(err)
	}
	return tokenString, nil
}

func login(w http.ResponseWriter, r *http.Request) {
	var user User
	var jwt JWT
	var error Error

	json.NewDecoder(r.Body).Decode(&user)
	password := user.Password

	row := db.QueryRow("SELECT* FROM users WHERE email=$1", user.Email)
	err := row.Scan(&user.ID, &user.Email, &user.Password)
	if err != nil {
		if err == sql.ErrNoRows {
			error.Message = "User does not exist"
			respondWithError(w, http.StatusBadRequest, error)
			return
		} else {
			log.Fatal(err)
		}
	}

	hashedPassword := user.Password
	err = bcrypt.CompareHashAndPassword([]byte(hashedPassword), []byte(password))
	if err != nil {
		error.Message = "Invalid password"
		respondWithError(w, http.StatusUnauthorized, error)
		return
	}

	token, err := GenerateToken(user)
	if err != nil {
		log.Fatal(err)
	}

	w.WriteHeader(http.StatusOK)
	jwt.Token = token
	respondWithData(w, jwt)
}

func protected(w http.ResponseWriter, r *http.Request) {
	fmt.Println("protected invoked")
}

func tokenVerifyMiddleware(next http.HandlerFunc) http.HandlerFunc {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		var errorObject Error
		authHeader := r.Header.Get("Authorization")
		bearerToken := strings.Split(authHeader, " ")

		if len(bearerToken) == 2 {
			authToken := bearerToken[1]

			token, error := jwt.Parse(authToken, func(token *jwt.Token) (interface{}, error) {
				if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
					return nil, fmt.Errorf("There was an error")
				}

				return []byte("secret"), nil
			})

			if error != nil {
				errorObject.Message = error.Error()
				respondWithError(w, http.StatusUnauthorized, errorObject)
				return
			}

			if token.Valid {
				next.ServeHTTP(w, r)
			} else {
				errorObject.Message = error.Error()
				respondWithError(w, http.StatusUnauthorized, errorObject)
				return
			}
		} else {
			errorObject.Message = "Invalid token."
			respondWithError(w, http.StatusUnauthorized, errorObject)
			return
		}
	})
}
