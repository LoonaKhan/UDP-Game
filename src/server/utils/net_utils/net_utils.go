package net_utils

import (
	"encoding/json"
	"fmt"
)

func FormatRes[T any](resData T, header string) []byte {
	/*
		marshals the sent data to json
		appends the prefix to the data
	*/
	res, _ := json.Marshal(resData)
	stringified := fmt.Sprintf("%s%s", header, string(res))
	return []byte(stringified)
}
