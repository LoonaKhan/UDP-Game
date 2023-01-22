package chunks

import (
	"fmt"
	"os"
	"server/err_handling"
	"sync"
)

// file handle
var ChunksFile, FOpenErr = os.Create("chunks.txt")
var CfileMut sync.Mutex

func WriteChunk(mut *sync.Mutex, f *os.File, binData []byte) {
	// writes data to chunks
	// mostly a debug feature.
	// todo: use a mutex. just lock and unlock

	mut.Lock()
	defer mut.Unlock()

	_, err := f.WriteString("[")
	err_handling.Handle(err)
	for b := range binData {
		_, err = f.WriteString(fmt.Sprintf("%d ", binData[b]))
		err_handling.Handle(err)
	}
	_, err = f.WriteString("]\n")
	err_handling.Handle(err)
}
