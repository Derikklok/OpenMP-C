# ⚡ QUICK START - 3 Terminals Setup# 🚀 Quick Start Guide - Eye Glaze System



Simple visual guide to get the Eye Glaze system running in 3 separate terminals.## One Command to Start Everything! 🎯



---### **Prerequisites:**

- Node.js (v16+)

## 🎯 Overview- Python (3.8-3.11)

- npm

You need **3 PowerShell terminals** running simultaneously:

---

```

Terminal 1: Flask Backend    (Port 5000) 🔬## 🏃 **Quick Start (3 Steps)**

Terminal 2: Node.js Backend  (Port 5174) ⚙️

Terminal 3: React Frontend   (Port 5173) 🎨### **1. Install Dependencies (First Time Only)**

```

```bash

---# Install root dependencies (concurrently)

npm install

## 🚀 Quick Start

# Install all project dependencies

### 📍 **TERMINAL 1: Flask Backend (ML Model)**npm run install-all



```powershell# Install Flask dependencies separately

# Navigate to Flask foldernpm run install-flask

cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\flask_backend"```



# Activate virtual environment### **2. Configure Environment Variables**

.\.venv311\Scripts\Activate.ps1

Ensure these files exist with proper configuration:

# Start Flask- `flask_backend/.env` (Flask config - port 5000)

python app.py- `eye-glaze-server-main/.env` (MongoDB, Cloudinary, Gemini API keys)

```

### **3. Start Everything!**

**Expected:** `✅ Model loaded successfully!` + `Running on http://127.0.0.1:5000`

```bash

---npm start

```

### 📍 **TERMINAL 2: Node.js Backend (API Server)**

**That's it!** 🎉

```powershell

# Navigate to Node.js folderThis single command starts:

cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\eye-glaze-server-main"- ✅ Flask Backend (Port 5000) - ML Model

- ✅ Node.js Backend (Port 5174) - API Server  

# Start Node.js- ✅ React Frontend (Port 5173) - Web UI

npm run dev

```---



**Expected:** `Server running on port: http://localhost:5174`## 📋 **Available Scripts**



---| Command | Description |

|---------|-------------|

### 📍 **TERMINAL 3: React Frontend (Web UI)**| `npm start` | 🚀 Start all 3 services (kills all if one fails) |

| `npm run start:dev` | 🔧 Start all 3 services (keeps running if one fails) |

```powershell| `npm run flask` | Start Flask backend only (Windows) |

# Navigate to React folder| `npm run flask:unix` | Start Flask backend only (Linux/Mac) |

cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\eye-glaze-client-react-vite-main"| `npm run node` | Start Node.js backend only |

| `npm run react` | Start React frontend only |

# Start React| `npm run install-all` | Install all dependencies |

npm run dev| `npm run install-flask` | Install Flask Python dependencies |

```| `npm run test` | Run integration tests |

| `npm run health` | Check if all services are running |

**Expected:** `Local: http://localhost:5173/`

---

---

## 🎨 **Console Output**

## 🌐 Access the App

When you run `npm start`, you'll see color-coded logs:

Open in your browser:

``````

http://localhost:5173[FLASK]  🔬 Flask Backend - Port 5000

```[NODE]   ⚙️  Node.js Backend - Port 5174

[REACT]  🎨 React Frontend - Port 5173

---```



## 🛑 To StopEach service's logs will be prefixed with its name in color:

- 🔵 **FLASK** (Blue)

In each terminal, press: `Ctrl + C`- 🟡 **NODE** (Yellow)

- 🟢 **REACT** (Green)

---

---

## 🔄 First-Time Setup

## 🔗 **Access the Application**

### Only needed once:

Once all services are running:

**Terminal 1 (Flask):**

```powershell| Service | URL |

cd flask_backend|---------|-----|

python -m venv .venv311| **🎨 Web App** | http://localhost:5173 |

.\.venv311\Scripts\Activate.ps1| **⚙️ Node.js API** | http://localhost:5174/api/health |

pip install -r requirements.txt| **🔬 Flask API** | http://localhost:5000/health |

```

---

**Terminal 2 (Node.js):**

```powershell## 📦 **Project Structure**

cd eye-glaze-server-main

npm install```

```Final_project/

├── package.json                    # 🎯 Root - Run "npm start" here!

**Terminal 3 (React):**│

```powershell├── flask_backend/                  # 🔬 Flask ML Backend (Port 5000)

cd eye-glaze-client-react-vite-main│   ├── start.bat                   # Windows startup script

npm install│   ├── start.sh                    # Linux/Mac startup script

```│   ├── app.py                      # Flask application

│   ├── Model/                      # TensorFlow model

---│   └── requirements.txt            # Python dependencies

│

## ✅ Checklist├── eye-glaze-server-main/          # ⚙️ Node.js Backend (Port 5174)

│   ├── index.js                    # Express server

Before starting:│   ├── package.json                # Node.js dependencies

- [ ] Python 3.8-3.11 installed│   └── .env                        # MongoDB, Cloudinary, Gemini config

- [ ] Node.js 16+ installed│

- [ ] Flask dependencies installed└── eye-glaze-client-react-vite-main/  # 🎨 React Frontend (Port 5173)

- [ ] Node.js dependencies installed    ├── src/                        # React components

- [ ] React dependencies installed    ├── package.json                # React dependencies

- [ ] `.env` files configured    └── vite.config.ts              # Vite configuration

- [ ] Model file exists: `flask_backend/Model/best_dual_stream_model.keras````



------



## 📖 Full Documentation## 🔧 **First-Time Setup**



For detailed setup and troubleshooting, see: **`README.md`**### **Complete Setup Flow:**



---```bash

# 1. Navigate to project root

**That's it! Simple and straightforward.** 🎉cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project"


# 2. Install root dependencies
npm install

# 3. Install all project dependencies
npm run install-all

# 4. Install Flask dependencies
npm run install-flask

# 5. Configure environment variables
# Edit flask_backend/.env
# Edit eye-glaze-server-main/.env

# 6. Start everything!
npm start
```

---

## ⚠️ **Troubleshooting**

### **Issue: `concurrently` not found**
```bash
npm install
```

### **Issue: Flask virtual environment not found**
```bash
cd flask_backend
python -m venv .venv311
.\.venv311\Scripts\Activate.ps1
pip install -r requirements.txt
```

### **Issue: Port already in use**
```bash
# Windows - Kill processes on ports
netstat -ano | findstr :5000
netstat -ano | findstr :5174
netstat -ano | findstr :5173

# Then kill the process
taskkill /PID <process_id> /F
```

### **Issue: One service fails to start**
Use `start:dev` instead of `start` to keep other services running:
```bash
npm run start:dev
```

Then debug the failing service separately:
```bash
npm run flask   # Test Flask
npm run node    # Test Node.js
npm run react   # Test React
```

---

## 🧪 **Testing**

### **Check if services are running:**
```bash
npm run health
```

### **Run integration tests:**
```bash
npm run test
```

### **Manual testing:**
```bash
# Flask health
curl http://localhost:5000/health

# Node.js health
curl http://localhost:5174/api/health

# React (open in browser)
start http://localhost:5173
```

---

## 🛑 **Stopping Services**

Press `Ctrl+C` in the terminal where you ran `npm start`.

This will gracefully shut down all three services.

---

## 💡 **Tips**

1. **Keep terminal open** - Don't close the terminal window where services are running

2. **Check logs** - All service logs appear in the same terminal with color-coded prefixes

3. **Restart after changes:**
   - **Flask**: `Ctrl+C` then `npm start` (code changes require restart)
   - **Node.js**: Auto-restarts with `nodemon`
   - **React**: Auto-reloads with Vite HMR

4. **Environment variables** - Restart services after changing `.env` files

5. **Database connection** - Ensure MongoDB Atlas is accessible (requires internet)

---

## 🎯 **Recommended Workflow**

```bash
# 1. Start all services in one terminal
npm start

# 2. Open in browser
http://localhost:5173

# 3. Code in your editor

# 4. Save changes (React/Node.js auto-reload)

# 5. For Flask changes, restart:
Ctrl+C
npm start
```

---

## 📊 **Service Dependencies**

```
React Frontend (5173)
    ↓
    ├─→ Node.js Backend (5174)
    │       ↓
    │       ├─→ MongoDB Atlas
    │       ├─→ Cloudinary
    │       └─→ Google Gemini API
    │
    └─→ Flask Backend (5000)
            ↓
            └─→ TensorFlow Model
```

All services must be running for full functionality.

---

## ✅ **System Check**

Before starting, ensure:
- [ ] Node.js installed (`node --version`)
- [ ] Python installed (`python --version`)
- [ ] npm installed (`npm --version`)
- [ ] `flask_backend/.env` exists
- [ ] `eye-glaze-server-main/.env` exists
- [ ] MongoDB connection string configured
- [ ] Cloudinary credentials configured
- [ ] Flask model file exists: `flask_backend/Model/best_dual_stream_model.keras`

---

## 🎉 **Success!**

If you see:
```
[FLASK] ✅ Model loaded successfully!
[NODE]  ✅ Connected to MongoDB
[REACT] ✅ Local: http://localhost:5173
```

**You're ready to go!** Open http://localhost:5173 🚀

---

## 📚 **More Information**

- **Full Documentation**: `README.md`
- **Integration Details**: `INTEGRATION_COMPLETE.md`
- **Flask Backend**: `flask_backend/README.md`
- **Node.js Backend**: `eye-glaze-server-main/README.md`

---

**Last Updated:** November 1, 2025  
**Quick Start Version:** 2.0 (npm-based)  
**Status:** ✅ Production Ready
