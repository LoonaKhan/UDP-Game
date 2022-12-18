package addys

import (
	"net"
	p "server/db/models/players"
)

/*
the addy map maps all online clients to players they login as.
we map addy's to players.
only 1 client can control 1 player and vice versa.
this prevents  client from hijacking other players.
this persists so long as a client is connected.

the addy map also keeps track of all our clients
*/

var Addys = map[p.Player]*net.UDPAddr{}

func Insert(plr p.Player, addy *net.UDPAddr) { // adds a player/addy keypair
	Addys[plr] = addy
}

func PlayerExists(plr p.Player) bool { // checks if a player is already mapped
	_, exists := Addys[plr]
	return exists
}

func AddyMatch(plr p.Player, addy *net.UDPAddr) bool {
	// used to check if a client is logged in and using the right player.
	// used upon any request
	return Addys[plr] == addy
}

func Disconnect(addys *map[p.Player]*net.UDPAddr, plr p.Player) {
	/*
		we cant disconnect a player from the server side.
		however, we can order them to disconnect technically.
		regardless, we delete the client's association with their player, meaning they are effectively kicked.
		we can make the gameclient auto disocnnect after losing the player
	*/
	delete(*addys, plr) // now there is no more addy connected and that player is freed
}

func AllOnline(plrs *[]p.Player) {
	for plr := range Addys {
		*plrs = append(*plrs, plr)
	}
}

func DialWorker(addys *map[p.Player]*net.UDPAddr) {
	for {
		for plr, addr := range Addys {
			_, err := net.DialUDP("udp4", nil, addr)
			if err != nil { // if player is not connected, disconnect
				Disconnect(addys, plr)
			}
		}
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
