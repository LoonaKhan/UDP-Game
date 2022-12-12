package main

import (
	"fmt"
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
)

type Player struct {
	gorm.Model
	Name   string
	X      int
	Y      int
	Online bool
}

func main() {
	// connect
	db, err := gorm.Open(sqlite.Open("file::memory:?cache=shared"), &gorm.Config{})
	if err != nil {
		panic(err)
	}
	fmt.Println("connected")

	// migrate all the schema
	err = db.AutoMigrate(&Player{})
	fmt.Println("migrated")

	// crud
	db.Create(&Player{Name: "moona", X: 1, Y: 1, Online: true}) // create just requires a struct
	db.Create(&Player{Name: "moona", X: 1, Y: 1, Online: true})
	fmt.Println("created")

	var p Player
	db.First(&p, 1) // gets the first player of id: 1
	fmt.Println(p)

	var players []Player
	_ = db.Find(&players) // find can return multiple values. give no condition for all elements
	for i := range players {
		fmt.Println(i, ": ", players[i])
	}

}
