package players

import "gorm.io/gorm"

type Player struct {
	gorm.Model

	name   string
	X      int
	Y      int
	online bool
}
