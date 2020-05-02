package pointers

import( 
  "fmt"
  "errors"
)

// Bitcoin represents a bitcoin
type Bitcoin int

// Wallet represents a bank account
type Wallet struct {
  balance Bitcoin 
}

// Deposit adds amount to account balance
func (w *Wallet) Deposit(amount Bitcoin) {
  w.balance += amount
}

// Withdraw removes amount from account balance
func (w *Wallet) Withdraw(amount Bitcoin) error {
  if amount > w.balance {
    return errors.New("cannot withdraw, insufficient funds")
  }
  w.balance -= amount
  return nil
}

// Balance returns the account balance
func (w *Wallet) Balance() Bitcoin {
  return w.balance
}

func (b Bitcoin) String() string {
  return fmt.Sprintf("%d BTC", b)
}
