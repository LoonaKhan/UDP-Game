package players

import "gorm.io/gorm"

type Player struct {
	// todo: prevent people from setting an ID
	//		constructor?
	gorm.Model

	Name string `json:"name" gorm:"unique"`
	// add in a hashed password later?
	X int `json:"x"`
	Y int `json:"y"`
}
