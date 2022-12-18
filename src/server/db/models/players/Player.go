package players

import "gorm.io/gorm"

type Player struct {
	// todo: prevent people from setting an ID
	//		constructor?
	gorm.Model

	Name string `json:"name"`
	X    int    `json:"x"`
	Y    int    `json:"y"`
}
