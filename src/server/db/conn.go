package db

import (
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
	"server/conf"
	"sync"
)

var Conn, Conn_err = gorm.Open(sqlite.Open(conf.MEM), &gorm.Config{SkipDefaultTransaction: true})
var ConnMut = sync.Mutex{}
