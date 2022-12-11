package main

import (
	"fmt"
	"github.com/pkg/errors"
)

func f(n int) error {
	if n < 0 {
		return errors.New("must be greater than 0")
	}
	fmt.Println(n)
	return nil
}

func main() {
	err := f(1)
	if err != nil {
		fmt.Printf("%+v\n", err)
	}
	err = f(-1)
	if err != nil {
		fmt.Printf("%+v\n", err)
	}
}
