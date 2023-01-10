package main

import (
	"fmt"
	"github.com/aquilax/go-perlin"
)

/*
	as expected, values range from [-1,1] and average at 0

	we then store the value and can use it in a variety of places
		map the perlin noise value to a default value
		use another noise value to fine-tune it

	biome
	multiply the value by 1000(large num) and scale it.
	biomes next to eachother also have their ranges next to eachother
		-1000, -600: water
		-599, -200: beach
		-199, 200: plains
		201, 600: forest
		601, 1000: mountain
		etc
	biome corresponds to a base colour code. (-700(anything thats water) -> blue(0,0,255))
	add another value to determine the specific shade and details
		offset red, blue or greens


	height: based on biome
		biome corresponds to a default height?
		perlin noise value to offset it a bit

*/

var low_val, high_val, avg float64 = 0, 0, 0

const size = 10000

var vals [size][size]float64

var alpha float64 = 2
var beta float64 = 2
var n int32 = 3
var seed int64 = 50

func main() {

	p := perlin.NewPerlin(alpha, beta, n, seed)

	for x := 0; x < size; x++ {
		for y := 0; y < size; y++ {
			noise := p.Noise2D(float64(x)/10, float64(y)/10)
			vals[x][y] = noise
			avg = noise
			if noise > high_val {
				high_val = noise
			}
			if noise < low_val {
				low_val = noise
			}
		}
	}

	/*for x := range vals {
		for y := range vals {
			fmt.Printf("[%d, %d](%f, %f): %f\n", x, y, float64(x)/10, float64(y)/10, vals[x][y])
		}
	}*/
	fmt.Printf("Hight: %f, Low: %f, avg: %f\n", high_val, low_val, avg)

}
