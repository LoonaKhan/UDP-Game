package globvars

import "github.com/aquilax/go-perlin"

const SEED = 50
const RENDER_DISTANCE = 16
const CHUNK_SIZE = 16
const TIMEOUT = 5

const a float64 = 1.5 // as (a -> 1), it gets noisier
const b float64 = 1   // harmonic spacing/scaling
const n int32 = 4     // number of iterations. more = means more variance

var P = perlin.NewPerlin(a, b, n, SEED)
