package methods

import (
	"encoding/json"
	"fmt"
	"github.com/pkg/errors"
	"net"
	"server/routes/route_structs"
	rs "server/routes/route_structs"
	"strings"
	"time"
)

func ParseReq(buffer []byte) (header rs.Header, idx int, err error) { // ensures the index and headers are valid
	idx = strings.Index(string(buffer), "|")
	if idx == -1 {
		return header, idx, errors.New("'|' not found")
	}

	// parses header
	header_buff := buffer[:idx]
	err = json.Unmarshal(header_buff, &header)
	if err != nil { // header invalid
		fmt.Println(err)
		return header, idx, err
	}

	return header, idx, nil
}

func VerifyOnline(c *net.UDPConn, id uint) {
	for {
		time.Sleep(4 * time.Second)
		req := fmt.Sprintf("{\"method\":\"syn\", \"cred\":%d}|{}", id)
		c.Write([]byte(req))
	}
}

func UpdateCred(id uint, cred *uint) {
	*cred = id
}

func ReadRes(c *net.UDPConn, cred *uint) {
	for {
		buffer := make([]byte, 8192)
		n, _, _ := c.ReadFromUDP(buffer)

		header, idx, err := ParseReq(buffer)
		if err != nil {
			continue
		}

		if header.Method == "players" { // todo: keep track of all players
			continue
		} else if header.Method == "login" {
			fmt.Println(string(buffer))
			var playerid route_structs.PlayerID
			err := json.Unmarshal(buffer[idx+1:n], &playerid)
			if err != nil {
				fmt.Println(err)
				continue
			}
			UpdateCred(playerid.Id, cred)
			go VerifyOnline(c, *cred)
		} else if header.Method == "get_chunk" {
			fmt.Println(string(buffer[:idx]))
			fmt.Println(buffer[idx+1 : n])
		} else {
			if n > 0 {
				fmt.Println("res: ", string(buffer))
			}
		}
	}
}
