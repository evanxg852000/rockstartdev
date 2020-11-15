package main

import (
	"flag"
	"fmt"
	"log"
	"net"
	"path/filepath"
)

var port int
var rootDir string

func init() {
	flag.IntVar(&port, "port", 8080, "port number")
	flag.StringVar(&rootDir, "rootDir", "public", "root directory")
	flag.Parse()
}

func main() {
	server := fmt.Sprintf(":%d", port)
	listener, err := net.Listen("tcp", server)
	if err != nil {
		log.Fatal(err)
	}

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go handleConn(conn)
	}
}

func handleConn(c net.Conn) {
	defer c.Close()
	absPath, err := filepath.Abs(rootDir)
	if err != nil {
		log.Fatal(err)
	}
	ftp.server(ftp.NewConn(c, absPath))
}
