package error_handling

import (
	"fmt"
	"os"
)

func Handle(err error) {
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}
