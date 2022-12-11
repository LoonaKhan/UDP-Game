package json_utils

import (
	"encoding/json"
	"io"
	"os"
	"server/err_handling"
)

func ReadJsonFile[T any](path string) T {
	file, err := os.Open(path)
	err_handling.Handle(err)

	defer file.Close()

	var data T
	bytes, err := io.ReadAll(file)

	err = json.Unmarshal(bytes, &data)
	err_handling.Handle(err)

	return data
}
