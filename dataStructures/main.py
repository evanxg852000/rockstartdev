from linkedlist import LinkedList

def main():
    ll = LinkedList()
    ll.add_front(12)
    ll.add_front(23)
    ll.add_back(11)
    ll.add_back(32)



    for n in ll.items():
        print(n.data, end='  ')

if __name__ == '__main__':
    main()
