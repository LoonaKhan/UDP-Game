package globvars

import "github.com/aquilax/go-perlin"

const SEED = 50
const RENDER_DISTANCE = 16
const CHUNK_SIZE = 16
const TIMEOUT = 5

const a float64 = 2
const b float64 = 2
const n int32 = 3

var P = perlin.NewPerlin(a, b, n, SEED)
