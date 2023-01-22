package chunks

import (
	"fmt"
	"os"
	"server/err_handling"
)

// file handle
var ChunksFile, FOpenErr = os.Create("chunks.txt")

func WriteChunk(f *os.File, binData []byte) {
	// writes data to chunks
	// mostly a debug feature.

	_, err := f.WriteString("[")
	err_handling.Handle(err)
	for b := range binData {
		_, err = f.WriteString(fmt.Sprintf("%d ", binData[b]))
		err_handling.Handle(err)
	}
	_, err = f.WriteString("]\n")
	err_handling.Handle(err)
}
