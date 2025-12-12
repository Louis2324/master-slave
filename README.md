
# **Master Slave Bluetooth Communication**

## **Overview**

This project uses two Arduino boards and two HC-05 Bluetooth modules to create a simple wireless control link.
The **master Arduino** sends a `'1'` or `'0'` depending on a button press, and the **slave Arduino** receives that data and blinks an LED when it receives `'1'`.

There are **three Arduino sketches**:

* `btconfig.ino` → used only for configuring HC-05 modules in AT mode
* `master.ino` → runs on the master Arduino after configuration
* `slave.ino` → runs on the slave Arduino after configuration

---

## **1. btconfig.ino (Configuration Mode)**

This sketch is used **only when setting up the HC-05 modules in AT mode**.
It passes data between the Serial Monitor and the HC-05 so you can type AT commands.

### **Entering AT mode**

1. Power OFF HC-05
2. Hold the **KEY** button
3. Power ON while holding
4. LED will blink **slowly (1 blink per 2 seconds)** → AT mode active

### **LED patterns**

| State                      | Meaning                     |
| -------------------------- | --------------------------- |
| Slow blinking (1 every 2s) | AT mode                     |
| Fast blinking              | Normal mode (not connected) |
| Two quick blinks, pause    | Connected in data mode      |

---

## **2. Setting up the SLAVE module**

Open Serial Monitor at **38400 baud**.

Send:

```
AT
```

Should reply:

```
OK
```

Set the module to slave:

```
AT+ROLE=0
```

Get the slave’s Bluetooth address:

```
AT+ADDR?
```

It will look something like:

```
+ADDR:98D3:31:FD1234
```

You will use this on the master.

---

## **3. Setting up the MASTER module**

Enter AT mode again using the same steps.

Set master mode:

```
AT+ROLE=1
```

Now format the slave address for binding.
Example slave address:

```
98D3:31:FD1234
```

Formatted:

```
98D3,31,FD1234
```

Bind master → slave:

```
AT+BIND=98D3,31,FD1234
```

(Optional but useful):

```
AT+PAIR=98D3,31,FD1234,20
AT+LINK=98D3,31,FD1234
```

When connected, the master HC-05’s LED changes to:

* **Two quick blinks → pause → repeat**

---

## **4. Uploading the Communication Sketches**

After both modules are configured:

1. Disconnect power to exit AT mode
2. Re-power the HC-05 (they will now enter normal mode)
3. LEDs will blink fast until they auto-connect
4. Upload the communication sketches:

**Master Arduino → `master.ino`**
**Slave Arduino → `slave.ino`**

---

## **5. What the scripts do**

### **master.ino**

* Reads a pushbutton
* Toggles state each time the button is pressed
* Sends `'1'` when toggled ON
* Sends `'0'` when toggled OFF

### **slave.ino**

* Listens for Bluetooth data
* If it receives `'1'`: starts blinking an LED
* If it receives `'0'`: stops blinking and turns LED off

---

## **6. Summary**

1. Use `btconfig.ino` to configure both HC-05 modules
2. Set one to master and one to slave
3. Get the slave’s address
4. Bind the master to the slave
5. Upload `master.ino` and `slave.ino`
6. Press the button on the master Arduino → LED blinks on the slave Arduino

This is an overview of the project

---