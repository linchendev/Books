//id重复分配

package main

import (
	"container/heap"
	"fmt"
)

// An IntHeap is a min-heap of ints.
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IntHeap) Push(x interface{}) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, x.(int))
}

func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

//返回[1,10]区间的数据
type UniqueId struct {
	min, max    int
	cur         int
	release_map map[int]bool
	//release_heap IntHeap
	ch chan int
}

func NewUniqueId(min, max int) *UniqueId {
	if min > max || min < 0 || max < 0 {
		return nil
	}
	u := &UniqueId{
		min:         min,
		max:         max,
		cur:         min,
		release_map: make(map[int]bool),
		ch:          make(chan int, max-min),
	}
	return u
}

func Begin(m map[int]bool) (int, bool) {
	for k, _ := range m {
		delete(m, k)
		return k, true
	}
	return 0, false
}

func GetChannel(ch chan int) (int, bool) {
	select {
	case id := <-ch:
		return id, true
	default:
		return 0, false
	}
}

func (this *UniqueId) Get() (int, bool) {
	if this.cur < this.min+(this.max-this.min)/2 {
		fmt.Println("first....")
		this.cur++
		return this.cur, true
	}
	if id, ok := GetChannel(this.ch); ok {
		fmt.Println("second....")
		delete(this.release_map, id)
		return id, ok
	}
	if this.cur < this.max {
		fmt.Println("three....")
		this.cur++
		return this.cur, true
	}
	return 0, false
}

func (this *UniqueId) Put(id int) bool {
	if _, e := this.release_map[id]; !e {
		this.ch <- id
		this.release_map[id] = true
		return true
	}
	return false
}

func main() {
	ids := NewUniqueId(1, 20)
	for i := 0; i < 10; i++ {
		id, ok := ids.Get()
		if !ok {
			fmt.Println("get error")
			return
		}
		fmt.Println(id)
		if i%3 == 0 {
			if ids.Put(id) != true {
				fmt.Println("put error")
				return
			}
		}
	}
}
