package main

import (
	"fmt"
	c "server/db/models/chunks"
)

// tests perlin noise within a chunk

func chunkNoiseTest() {
	var avg, high, low float64 = 0, 0, 0
	var noises []float64 // noises can be used to keep track of std::variance

	chunk := c.Init(1, 1)
	fmt.Printf("Chunk: [%d, %d]\n", chunk.X, chunk.Y)
	for i := range chunk.Blocks {
		avg += chunk.Blocks[i].Noise
		noises = append(noises, chunk.Blocks[i].Noise)
		if chunk.Blocks[i].Noise > high {
			high = chunk.Blocks[i].Noise
		}
		if chunk.Blocks[i].Noise < low {
			low = chunk.Blocks[i].Noise
		}
	}

	avg /= float64(len(chunk.Blocks))
	fmt.Printf("high: %f, low: %f, avg: %f\n", high, low, avg)

	fmt.Printf("[ ")
	for n := range noises {
		fmt.Printf("%f, ", noises[n])
	}
	fmt.Printf("]\n")
}

func main() {
	chunkNoiseTest()
}
