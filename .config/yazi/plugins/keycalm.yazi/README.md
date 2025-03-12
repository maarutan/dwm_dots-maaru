---
https://github.com/user-attachments/assets/53257156-e531-4aa5-9865-6b42f623b5a9

### **KeyCalm: Smart Key Rate Limiter for Yazi**
🚀 **KeyCalm** is a **plugin for Yazi** that prevents excessive key spamming by blocking keys after a certain number of presses within a short time.

🔹 **Customizable settings**
🔹 **Auto-unblock with notifications**
🔹 **Supports J/K navigation keys (configurable)**
🔹 **ESC resets the counters**
---

## **Installation**

Make sure you have Yazi installed and configured. Then, install **KeyCalm**:

### **1️⃣ Clone the repository**

```sh
git clone https://github.com/maarutan/keycalm ~/.config/yazi/plugins/keycalm
```

## or `ya`

```sh
ya pack -a maarutan/keycalm
```

### **2️⃣ Add key bindings to `keymap.toml`**

Edit `~/.config/yazi/keymap.toml` and add:

```toml
[[manager.prepend_keymap]]
on   = "j"
run  = "plugin keycalm --args=j"
desc = "KeyCalm protection for j"

[[manager.prepend_keymap]]
on   = "k"
run  = "plugin keycalm --args=k"
desc = "KeyCalm protection for k"

[[manager.prepend_keymap]]
on   = "<Esc>"
run  = "plugin keycalm --args=<Esc>"
desc = "Reset KeyCalm block"
```

### **3️⃣ Configuration**

You can **customize KeyCalm** by adding the setup function to `init.lua`:

```lua
require("keycalm"):setup({
    limit = 10,  -- Number of presses before blocking
    delay = 3,   -- Block duration in seconds (also notification duration)
    notify_title = "Hold it, {user}!",  -- Notification title
    notify_message = "🤠 Take it easy, cowboy!",  -- Message when blocked
    notify_unblock = "      {key} 🥳",  -- Message when unblocked
})
```

---

## **How It Works**

1. Pressing `j` or `k` increases the counter.
2. If **you press it 10 times**, the key is **blocked for 3 seconds**.
3. A **notification appears**, saying:
   > _"Hold it, Cowboy!"_
4. After **3 seconds**, the key is unblocked.
5. Pressing `<Esc>` **resets everything instantly**.

---

## **License**

MIT License

---

Let me know if you want any tweaks! 🚀🔥
