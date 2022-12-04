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
	id        string    // id of the session
	expiresAt time.Time // time the session will expire
	uid       int       // id of a user in the database
}

func Init(given_uid int) {
	// create new_id
	new_id := uuid.New().String()

	// append to Sessions
	Sessions[new_id] = Session{
		id:        new_id,
		expiresAt: time.Now().Add(5 * time.Second), // subject to change
		uid:       given_uid,
	}
}

func Delete(sess *string) {
	delete(Sessions, *sess)
}
