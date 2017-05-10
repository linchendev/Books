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
	min, max     int
	cur          int
	release_map  map[int]bool
	release_heap IntHeap
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
	}
	heap.Init(&u.release_heap)
	return u
}

func (this *UniqueId) Get() (int, bool) {
	if len(this.release_heap) >= (this.max-this.min)/2 {
		id := heap.Pop(&this.release_heap).(int)
		delete(this.release_map, id)
		fmt.Println("heap1...")
		return id, true
	}
	if this.cur <= this.max {
		fmt.Println("first....")
		id := this.cur
		this.cur++
		return id, true
	}
	if len(this.release_heap) != 0 {
		id := heap.Pop(&this.release_heap).(int)
		delete(this.release_map, id)
		fmt.Println("heap2...")
		return id, true
	}
	return 0, false
}

func (this *UniqueId) Put(id int) bool {
	if _, e := this.release_map[id]; !e {
		heap.Push(&this.release_heap, id)
		this.release_map[id] = true
		return true
	}
	return false
}

func main() {
	ids := NewUniqueId(1, 20)
	for i := 0; i < 40; i++ {
		id, ok := ids.Get()
		if !ok {
			fmt.Println("get error")
			return
		}
		fmt.Println(id)
		if i%2 == 0 {
			fmt.Println("put", id)
			if ids.Put(id) != true {
				fmt.Println("put error")
				return
			}
		}
	}
}
