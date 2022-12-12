package conf

import "server/json_utils"

type Conf struct {
	PORT            int    `json:"PORT"`
	CHUNK_SIZE      int    `json:"CHUNK_SIZE"`
	RENDER_DISTANCE int    `json:"RENDER_DISTANCE"`
	DB_file         string `json:"DB_FILE"`
	MEM             string `json:"MEM"`
}

var Config = json_utils.ReadJsonFile[Conf]("./conf/config.json")
var RENDER_DISTANCE = Config.RENDER_DISTANCE
var CHUNK_SIZE = Config.CHUNK_SIZE
var PORT = Config.PORT
var DB = Config.DB_file
var MEM = Config.MEM
