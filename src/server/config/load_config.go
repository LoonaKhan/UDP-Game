package config

import "server/json_utils"

var Config = json_utils.ReadJsonFile[map[string]int]("./config/config.json")
var RENDER_DISTANCE = Config["RENDER_DISTANCE"]
var CHUNK_SIZE = Config["CHUNK_SIZE"]
var GAME_SERVER_PORT = Config["GAME_SERVER_PORT"]
var HTTP_SERVER_PORT = Config["HTTP_SERVER_PORT"]
