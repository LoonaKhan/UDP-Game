package sessions

import (
	"github.com/google/uuid"
	"time"
)

/*
check if time is up
delete session
	removes from sessions object
session constructor?
*/

var Sessions map[string]Session // map of all our sessions

type Session struct {
	Id        string    // Id of the session
	ExpiresAt time.Time // time the session will expire
	Uid       int       // Id of a user in the database
}

func Init(given_uid int) {
	// create new_id
	new_id := uuid.New().String()

	// append to Sessions
	Sessions[new_id] = Session{
		Id:        new_id,
		ExpiresAt: time.Now().Add(5 * time.Second), // subject to change
		Uid:       given_uid,
	}
}

func Delete(sess string) {
	delete(Sessions, sess)
}
