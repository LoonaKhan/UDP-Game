package json_utils

import (
	"encoding/json"
	"io"
	"os"
	"server/error_handling"
)

func ReadJsonFile[T any](path string) T {
	file, err := os.Open(path)
	error_handling.HandleErr(err)

	defer file.Close()

	var data T
	bytes, err := io.ReadAll(file)

	err = json.Unmarshal(bytes, &data)
	error_handling.HandleErr(err)

	return data
}
