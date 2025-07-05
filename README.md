# 🍽️ Circular Queue Order Management System in C

This is a simple command-line based **Order Management System** implemented using **Circular Queue** in the C programming language. It simulates a restaurant order queue where customers can place orders from a menu and the system handles the order placement and serving using queue logic.

---

## 📌 Features

- ✅ Enqueue new customer orders (with multiple menu item selection)
- ✅ Dequeue/serve orders (FIFO logic)
- ✅ Display all current orders in the queue
- ❌ Prevent adding if queue is full
- ❌ Prevent serving if queue is empty
- 💬 Menu-driven user interface in terminal

---

## 🔧 Data Structure Used

**Circular Queue** implemented using a fixed-size array:
- Efficiently wraps around when the end of the array is reached
- Prevents shifting of elements like a linear queue
- Good for managing continuous incoming and outgoing tasks like orders

---

