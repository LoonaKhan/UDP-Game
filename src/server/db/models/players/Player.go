package players

import "gorm.io/gorm"

type Player struct {
	gorm.Model

	Name   string `json:"name"`
	X      int    `json:"x"`
	Y      int    `json:"y"`
	Online bool   `json:"online"`
}
