package addys

import (
	"fmt"
	"net"
	"server/conf"
	p "server/db/models/players"
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

var Addys = map[uint]Client{}

func Insert(plr p.Player, addy *net.UDPAddr) { // adds a player/client keypair
	c := Client{Addy: addy, Expiry: time.Now().Add(conf.TIMEOUT * time.Second)}
	Addys[plr.ID] = c
}

func PlayerExists(plr p.Player) bool { // checks if a player is already mapped
	_, exists := Addys[plr.ID]
	return exists
}

func AddyMatch(plr p.Player, addy *net.UDPAddr) bool {
	// used to check if a client is logged in and using the right player.
	// used upon any request
	//fmt.Println(Addys[plr.ID].Addy, " = ", addy, "=", (Addys[plr.ID].Addy.IP.Equal(addy.IP) && Addys[plr.ID].Addy.Port == addy.Port))
	return (Addys[plr.ID].Addy.IP.Equal(addy.IP) && Addys[plr.ID].Addy.Port == addy.Port)
}

func Disconnect(id uint) {
	/*
		we cant disconnect a player from the server side.
		however, we can order them to disconnect technically.
		regardless, we delete the client's association with their player, meaning they are effectively kicked.
		we can make the gameclient auto disocnnect after losing the player
	*/
	delete(Addys, id) // now there is no more addy connected and that player is freed
}

func AllOnline(plrs *[]p.Player) {
	for _ = range Addys {
		//*plrs = append(*plrs, plr) // todo: fix this
	}
}

func VerifyOnline(addys *map[uint]Client) {
	/*
		Runs constantly in the background.
		Checks if the given client has expired their time.
		if so, disconnect them
		//todo: verify online and synack fight over Addys. fix
	*/
	for {
		for plr, client := range *addys {
			fmt.Println("expiry:", client.Expiry.String())
			if time.Now().After(client.Expiry) {
				Disconnect(plr)
				fmt.Println("disconnected:", plr)
			}
		}
		time.Sleep(100 * time.Millisecond)
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
