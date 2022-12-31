package players

import "gorm.io/gorm"

type Player struct {
	gorm.Model

	Name string `json:"name" gorm:"unique"`
	// add in a hashed password later?
	X int `json:"x"`
	Y int `json:"y"`
}
