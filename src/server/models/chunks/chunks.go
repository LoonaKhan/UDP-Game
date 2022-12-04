package chunks

import "server/config"

func ToChunkCoords(pos []int) []int { // converts block coordinates to chunk coordinates
	chunkCoords := make([]int, 2)
	for i := range pos {
		chunkCoords[i] = int(pos[i] / config.CHUNK_SIZE)
		if chunkCoords[i] < 0 {
			chunkCoords[i] -= 1
		}
	}

	return chunkCoords
}

func ChunksInRenderDist(curCunk []int) [][]int { // returns all chunks within render distance
	chunks := [][]int{}
	i := 0
	for x := curCunk[0] - config.RENDER_DISTANCE; x < curCunk[0]+config.RENDER_DISTANCE; x++ {
		for y := curCunk[1] - config.RENDER_DISTANCE; y < curCunk[1]+config.RENDER_DISTANCE; y++ {
			chunks = append(chunks, []int{x, y})
			i++
		}
	}
	return chunks
}
