package main

import (
	"fmt"
)

type IDAlloc struct {
	idArr []uint
	size  uint

	read  int
	write int

	id uint
}

func NewIDAlloc(start uint, size uint) *IDAlloc {
	ids := &IDAlloc{
		idArr: make([]uint, size),
		size:  size,
		read:  0,
		write: 0,
		id:    start,
	}
	for i := start; i != start+size; i++ {
		ids.Put(i)
	}

	return ids
}

func (this *IDAlloc) Get() uint {
	if this.isReadFull() {
		t := this.id
		this.id++
		return t
	}

	t := this.idArr[this.read]
	this.read = this.nextRead()
	return t
}

func (this *IDAlloc) Put(t uint) {
	if this.isWriteFull() {
		//reset size
		this.size = this.size*2 + 128
		maxArr := make([]uint, this.size)
		copy(maxArr, this.idArr)
		this.idArr = maxArr
	}

	this.idArr[this.write] = t
	this.write = this.nextWrite()
}

func (this *IDAlloc) nextWrite() int {
	n := this.write + 1
	if uint(n) >= this.size {
		return 0
	}

	return n
}

func (this *IDAlloc) nextRead() int {
	n := this.read + 1
	if uint(n) >= this.size {
		this.read = 0
	}

	return n
}

func (this *IDAlloc) isWriteFull() bool {
	n := this.nextWrite()
	return this.read == n
}

func (this *IDAlloc) isReadFull() bool {
	return this.read == this.write
}

func main() {
	ids := NewIDAlloc(1, 100)
	for i := 0; i < 300; i++ {
		id := ids.Get()
		fmt.Println(id)
		ids.Put(id)
	}
}
