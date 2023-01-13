package main

import (
	"fmt"
	"net"
	"server/db/models/chunks"
	gv "server/globvars"
	"server/tests/clients/methods"
	"strconv"
	"sync"
	"time"
)

var postPlayer = "{\"method\":\"post_player\"}" + "|" + "{\"name\": \"%s\"}"
var login = "{\"method\":\"login\"}" + "|" + "{\"name\": \"%s\"}"
var queryChunk = "{\"method\":\"get_chunk\", \"cred\":%d}" + "|" + "{\"coords\":[%d,%d]}"
var updatePos = "{\"method\":\"update_pos\", \"cred\":%d}" + "|" + "{\"coords\":[%d,%d]}"

func RecieveChunks(c *net.UDPConn, cred *uint, thread *int, wg *sync.WaitGroup, isLoggedIn *sync.WaitGroup) {
	for {
		buffer := make([]byte, 2048)
		n, _, _ := c.ReadFromUDP(buffer)
		header, _, _ := methods.ParseReq(buffer)

		if header.Method == "login" && header.Code { // if we successfully login
			methods.UpdateCred(header.Cred, cred)
			isLoggedIn.Done()
			fmt.Printf("Thread %d is logged in\n", *thread)
			go methods.VerifyOnline(c, *cred)
		} else if header.Method == "get_chunk" && header.Code { // if we successfully post a chunk
			fmt.Printf("Thread %d has recieved %d bytes\n", *thread, n)
			wg.Done()
		} else if header.Method == "login" && !header.Code && *cred == 0 { // if we dont successfully login
			fmt.Printf("failed to login thread %d\n", *thread)
			time.Sleep(15 * time.Millisecond)
			c.Write([]byte(fmt.Sprintf(login, strconv.Itoa(*thread))))
		} else if header.Method == "players" { // ignores ack
			continue
		} else if header.Method == "post_player" && !header.Code { // if we dont successfully create a player
			fmt.Printf("failed to post player on thread %d\n", *thread)
			time.Sleep(15 * time.Millisecond)
			//c.Write([]byte(fmt.Sprintf(postPlayer, strconv.Itoa(*thread))))
		} else if header.Method == "update_pos" && !header.Code {
			fmt.Printf("failed to update pos on thread %d\n", *thread)
			time.Sleep(15 * time.Millisecond)
			c.Write([]byte(fmt.Sprintf(updatePos,
				strconv.Itoa(*thread),
				strconv.Itoa(*thread*gv.CHUNK_SIZE),
				strconv.Itoa(*thread*gv.CHUNK_SIZE))))
		} else if header.Method == "update_pos" {
			fmt.Printf("attempted to update thread %d\n", *thread)
			fmt.Println(string(buffer))
		} else if header.Method == "update_pos" && header.Code {
			fmt.Printf("updated pos on thread %d\n", *thread)
		} else if header.Method == "get_chunk" && !header.Code {
			fmt.Printf("failed to get chunk on thread %d\n", *thread)
			fmt.Println(string(buffer))
		}
	}
}

func client(wg *sync.WaitGroup, threadId int) {
	thisthread := threadId
	var IWG sync.WaitGroup
	var cred2 uint
	var pos = (thisthread * gv.RENDER_DISTANCE * gv.CHUNK_SIZE)
	var posChunk = chunks.ToChunkCoords([]int{pos, pos})

	CONN := "localhost:4000"
	// connection
	s, err := net.ResolveUDPAddr("udp4", CONN)
	c, err := net.DialUDP("udp4", nil, s)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer c.Close()

	var isLoggedIn sync.WaitGroup
	isLoggedIn.Add(1)

	// reads all responses incoming in a seperate thread
	go RecieveChunks(c, &cred2, &thisthread, &IWG, &isLoggedIn)

	c.Write([]byte(fmt.Sprintf(postPlayer, strconv.Itoa(thisthread))))
	c.Write([]byte(fmt.Sprintf(login, strconv.Itoa(thisthread))))

	isLoggedIn.Wait()

	start := time.Now() // start timestamp
	defer func(wg *sync.WaitGroup, start time.Time) {
		fmt.Printf("thread %d finished in %f seconds\n", thisthread, time.Since(start).Seconds())
		wg.Done()
	}(wg, start)
	c.Write([]byte(fmt.Sprintf(updatePos,
		int(cred2), pos, pos)))

	for x := posChunk[0]; x < (gv.CHUNK_SIZE + posChunk[0]); x++ {
		for y := posChunk[1]; y < (gv.CHUNK_SIZE + posChunk[1]); y++ {
			IWG.Add(1)
			c.Write([]byte(fmt.Sprintf(queryChunk, cred2, x, y)))
			time.Sleep(15 * time.Millisecond)
		}
	}

	IWG.Wait()
}

func main() {
	var wg sync.WaitGroup

	for i := 0; i < 20; i++ {
		wg.Add(1)
		go client(&wg, i)
		time.Sleep(10 * time.Millisecond)
	}

	wg.Wait()

}
