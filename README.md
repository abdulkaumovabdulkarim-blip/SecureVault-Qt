# SecureVault 🔐

**SecureVault** is a lightweight, secure desktop password manager built from scratch using **C++** and the **Qt Framework**. It allows users to safely store, manage, and edit their account credentials locally.

The project follows clean OOP principles, utilizes a custom Singleton backend for session management, and stores data in an optimized local binary format.

---

## ✨ Features

* **Secure Authentication:** User sign-up and sign-in functionality with input validation and local record checking.
* **Local Binary Storage:** Data is stored in structured binary files (`users.dat` and `vault.dat`), preventing plain-text data leakage.
* **Granular Data Isolation:** Users can only view, add, or modify their own credentials; other users' records are safely preserved and isolated.
* **Intuitive UI/UX:**
  * Clean, distraction-free **Main Menu** showcasing only website titles for shoulder-surfing privacy.
  * Interactive **QTableWidget** navigation (double-click a website to view or edit details).
  * Modal dynamic forms for adding and managing credentials seamlessly.

---

## 🛠️ Tech Stack & Architecture

* **Language:** C++
* **Framework:** Qt 6 (Widgets)
* **IDE:** Microsoft Visual Studio
* **Design Pattern:** Singleton (Core Engine), Object-Oriented Programming (OOP)
* **Storage:** Custom Binary File I/O (`std::fstream`)

---

## 🚀 Getting Started

### Prerequisites
* Windows 10 / 11
* Visual Studio (with *Desktop development with C++* and *Qt Visual Studio Tools* extension installed)
* Qt Framework
