# A. C-Advanced Mid Term Projects

## 1. Hanoi Bus Map:
#### 1.1. Techniques:
- Red-black tree to store routes and bus stops in graphs.
- Include `field.h` lib to read dataset from text file.
- Use the `dllist.h` lib in conjunction with the Dijkstra algorithm to find optimal route.
#### [1.2. Dataset](https://github.com/minhld99/C-Advanced/blob/master/Hanoi_BusMap/text.txt)
Crawl from Hanoi Bus official [website](http://timbus.vn/fleets.aspx). We only do test on a small amount of routes and leave the generalization for future.
## 2. EN-VI Dictionary:
#### 2.1. Techniques:
- Reference to `GTK+` from [Gnome](https://developer.gnome.org) for graphical interface.
- `B-Tree lib` allows find / add / edit / delete.
  - Why B-Tree: 
  ```
    - B-tree is self-balanced.
    - We need a data structure which is symmetrical and ordered in order to give access to all word definitions at the same time.
    - Using B-tree can access a large number of words directly on the floppy disk without using RAM, thanks to the unique structure of B-tree, time to access each words is the same with a very little differences and quite fast.
  ```
- `Soundex lib` to genarate searching suggestions.
#### [2.2. Dataset](https://github.com/minhld99/C-Advanced/blob/master/EN-VI_Dictionary/AnhViet.txt)

# B. C-Advanced Final
```
Updating...
```
