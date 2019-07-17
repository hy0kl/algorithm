package main

import (
	"fmt"
	"math/rand"
	"time"
)

// 生成一个区间范围的随机数,左闭右开
func generateRandom(min, max int) int {
	if min >= max {
		return max
	}

	rand.Seed(time.Now().UnixNano())
	randNum := rand.Intn(max - min)
	randNum += min

	return randNum
}

func redPack(amount int, number int) (list []int) {
	for i := number; i > 0; i-- {
		money := generateRandom(1, amount-i)
		list = append(list, money)
		amount = amount - money
	}

	// 剩余的钱随机分给一个人
	if amount > 0 {
		list[generateRandom(0, number)] += amount
	}

	return
}

func main() {
	list := redPack(100, 10)
	fmt.Printf("list: %#v\n", list)

	sum := 0
	for _, money := range list {
		sum += money
	}
	fmt.Printf("sum: %d\n", sum)
}
