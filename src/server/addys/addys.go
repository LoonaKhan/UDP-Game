package addys

import (
	"encoding/json"
	"fmt"
	"net"
	"server/conf"
	"server/db"
	p "server/db/models/players"
	rs "server/routes/route_structs"
	"time"
)

/*
the addy map maps all online clients to players they login as.
we map addy's to players.
only 1 client can control 1 player and vice versa.
this prevents  client from hijacking other players.
this persists so long as a client is connected.

the addy map also keeps track of all our clients
*/

type Client struct {
	/*
		a client is matched with a player.
		Each client must have an address and a client
	*/
	Addy   *net.UDPAddr
	Expiry time.Time
}

/*
We use a channel here because it is imperative to make sure all connected client are indeed connected
and likewise for disconnected players.
Because multiple threads will be writing to this map, it needs to be thread safe, hence a chan.
*/
var AddyChan = make(chan map[uint]Client, 1) /*w*/ // < ohayo nii san watashi wa addy-channn desu

func Insert(plr p.Player, addy *net.UDPAddr) { // adds a player/client keypair
	c := Client{Addy: addy, Expiry: time.Now().Add(conf.TIMEOUT * time.Second)}
	addys := <-AddyChan
	addys[plr.ID] = c
	AddyChan <- addys
}

func PlayerExists(plr p.Player) bool { // checks if a player is already mapped
	addys := <-AddyChan
	_, exists := addys[plr.ID]
	AddyChan <- addys
	return exists
}

func AddyMatch(plr p.Player, addy *net.UDPAddr) bool {
	// used to check if a client is logged in and using the right player.
	// used upon any request
	//fmt.Println(Addys[plr.ID].Addy, " = ", addy, "=", (Addys[plr.ID].Addy.IP.Equal(addy.IP) && Addys[plr.ID].Addy.Port == addy.Port))
	addys := <-AddyChan
	AddyChan <- addys
	return (addys[plr.ID].Addy.IP.Equal(addy.IP) && addys[plr.ID].Addy.Port == addy.Port)
}

func Disconnect(id uint, addys *map[uint]Client) {
	/*
		we cant disconnect a player from the server side.
		however, we can order them to disconnect technically.
		regardless, we delete the client's association with their player, meaning they are effectively kicked.
		we can make the gameclient auto disocnnect after losing the player
	*/
	if _, ok := (*addys)[id]; ok {
		delete(*addys, id) // now there is no more addy connected and that player is freed
		fmt.Println("disconnected:", id)
	}
}

func VerifyOnline(conn *net.UDPConn) {
	/*
		Runs constantly in the background.
		Checks if the given client has expired their time.
		if so, disconnect them
		then sends all currently existing players back to the client
	*/
	for {
		var plrs []p.Player
		var plrIds []uint
		addys := <-AddyChan

		for plr, client := range addys {
			if time.Now().After(client.Expiry) || time.Now().Equal(client.Expiry) { // disconnect
				Disconnect(plr, &addys)
			} else { // otherwise append them to the plr id's array
				plrIds = append(plrIds, plr)
			}
		}

		if len(addys) > 0 { // only sends back if there are clients to connect to
			db.Conn.Find(&plrs, "id IN ?", plrIds) // finds all players online
			var plist = rs.ListPlayers{Players: plrs}
			res, _ := json.Marshal(plist)
			res_str := string(res)

			// sends them to all clients
			for _, client := range addys {
				conn.WriteToUDP([]byte(fmt.Sprintf("players:%s", res_str)), client.Addy)
			}
		}
		AddyChan <- addys
	}
}

/*
we want to take an address and access its player
	client sends their player
	we verify if their address matches the associated player's addy
	client only needs the player's id
	if not, disconnect em

we want to find if the given player is already mapped (player key)

we can delete by accessing either using a player key or addy key(dont matter)

(player key)
its worse for a player to be controlled by many
than an address to control many unique players
more important to verify if a player is already mapped
*/
