package methods

import (
	"encoding/json"
	"fmt"
	"net"
	"server/routes/route_structs"
	"strings"
	"time"
)

func ParseHeader(buffer []byte) (method []byte, idx int) { // error handle for no semi colons
	idx = strings.Index(string(buffer), ":") + 1 // dont use a colon as that is used in json.
	method = buffer[:idx]
	//fmt.Printf(string(method))
	return method, idx
}

func VerifyOnline(c *net.UDPConn, id uint) {
	for {
		time.Sleep(4 * time.Second)
		c.Write([]byte(fmt.Sprintf("syn:{\"pid\": %d}", id)))
	}
}

func ReadRes(c *net.UDPConn) {
	for {
		buffer := make([]byte, 8192)
		n, _, _ := c.ReadFromUDP(buffer)

		method, idx := ParseHeader(buffer)
		if string(method) == "players:" { // todo: keep track of all players
			continue
		} else if string(method) == "login:" {
			fmt.Println(string(buffer))
			var playerid route_structs.PlayerID
			json.Unmarshal(buffer[idx:n], &playerid)
			go VerifyOnline(c, playerid.Id)
		} else {
			if n > 0 {
				fmt.Println(string(buffer))
			}
		}
	}
}
