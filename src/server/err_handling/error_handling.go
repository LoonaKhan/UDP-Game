package err_handling

import (
	"fmt"
)

func Handle(err error) { // panics. standalone good for fatal errors
	if err != nil {
		panic(err)
	}
}

//panic stops execution and goes up the stack trace until it exits the program
// after panicking, the function exits and runs the deferred functions
// by placing recover in the deferred function, you can resume the execution of the parent function

func Recover(msg string) { // if the error is not fatal, do this.
	if r := recover(); r != nil {
		fmt.Printf("Recovered: %s", msg)
	}
}
