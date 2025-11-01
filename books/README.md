# 🎯 Eye Glaze - Iris Stress Detection System

Complete AI-powered stress detection system through iris analysis using deep learning.

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                  React Frontend (Port 5173)                 │
│              Vite + TypeScript + Tailwind CSS               │
└─────────────┬──────────────────────────┬───────────────────┘
              │                          │
              │                          │
    ┌─────────▼─────────┐      ┌────────▼────────┐
    │  Node.js Backend  │      │  Flask Backend  │
    │   (Port 5174)     │      │   (Port 5000)   │
    │   Express + API   │      │  TensorFlow ML  │
    └─────────┬─────────┘      └─────────────────┘
              │
    ┌─────────▼─────────┐
    │  MongoDB Atlas    │
    │   Cloudinary      │
    │  Google Gemini    │
    └───────────────────┘
```

---

## 📋 Prerequisites

Before starting, ensure you have:

- ✅ **Python 3.8 - 3.11** (Recommended: 3.11)
- ✅ **Node.js 16+** (Recommended: 18+)
- ✅ **npm** (comes with Node.js)
- ✅ **Git** (optional, for cloning)

### Check Your Installations:

```powershell
python --version      # Should show Python 3.8-3.11
node --version        # Should show v16.x or higher
npm --version         # Should show 8.x or higher
```

---

## 📁 Project Structure

```
Final_project/
├── flask_backend/                    # 🔬 Flask ML Backend
│   ├── app.py                       # Flask application
│   ├── model_loader.py              # TensorFlow model loader
│   ├── preprocessing.py             # Image preprocessing
│   ├── custom_layers.py             # Neural network layers
│   ├── requirements.txt             # Python dependencies
│   ├── .env                         # Flask configuration
│   └── Model/
│       └── best_dual_stream_model.keras
│
├── eye-glaze-server-main/           # ⚙️ Node.js Backend
│   ├── index.js                     # Express server
│   ├── package.json                 # Node dependencies
│   ├── .env                         # MongoDB, Cloudinary, Gemini
│   ├── configs/                     # Database configs
│   ├── controllers/                 # Request handlers
│   └── routes/                      # API routes
│
└── eye-glaze-client-react-vite-main/  # 🎨 React Frontend
    ├── src/
    │   ├── pages/                   # Page components
    │   │   ├── Dashboard.tsx        # Main analysis page
    │   │   ├── Results.tsx          # Results & history
    │   │   ├── Login.tsx            # Authentication
    │   │   └── Register.tsx         # User registration
    │   ├── components/              # Reusable components
    │   └── contexts/                # React contexts
    ├── package.json                 # React dependencies
    └── vite.config.ts               # Vite config
```

---

## 🚀 Setup Guide

### **PART 1: Flask Backend Setup (ML Model Server)**

#### **Step 1.1: Navigate to Flask Backend**

```powershell
cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\flask_backend"
```

#### **Step 1.2: Create Virtual Environment**

```powershell
# Create virtual environment
python -m venv .venv311

# Activate virtual environment
.\.venv311\Scripts\Activate.ps1

# You should see (.venv311) in your prompt
```

**Note for Linux/Mac:**
```bash
python3 -m venv .venv311
source .venv311/bin/activate
```

#### **Step 1.3: Install Python Dependencies**

```powershell
# Upgrade pip first
python -m pip install --upgrade pip

# Install all dependencies
pip install -r requirements.txt
```

**This will install (~800MB):**
- tensorflow==2.18.0
- flask==3.1.2
- opencv-python==4.12.0.88
- numpy==2.0.2
- flask-cors==6.0.1
- And 42 more packages...

**Installation time:** 5-10 minutes depending on internet speed.

#### **Step 1.4: Configure Flask Environment**

Check if `.env` file exists:

```powershell
cat .env
```

**Required `.env` configuration:**

```properties
# Flask Backend Configuration

# Model Configuration
MODEL_PATH=Model/best_dual_stream_model.keras

# Flask Server Configuration
FLASK_HOST=0.0.0.0
FLASK_PORT=5000
FLASK_DEBUG=False

# CORS Configuration (React frontend URL)
CORS_ORIGINS=http://localhost:3000,http://localhost:5173

# Upload Configuration
MAX_CONTENT_LENGTH=16777216  # 16MB in bytes
UPLOAD_FOLDER=uploads

# Logging
LOG_LEVEL=INFO
```

#### **Step 1.5: Verify Model File Exists**

```powershell
# Check if model file exists
Test-Path Model\best_dual_stream_model.keras
# Should return: True
```

**If model doesn't exist:**
- Copy the trained model from your training environment
- Place it in: `flask_backend/Model/best_dual_stream_model.keras`

#### **Step 1.6: Test Flask Backend**

```powershell
# Start Flask server (keep this terminal open)
python app.py
```

**Expected output:**
```
============================================================================
🔬 IRIS STRESS DETECTION - FLASK API
============================================================================

[1/2] Loading model...
--------------------------------------------------------------------------------
✅ Model loaded successfully!
   Alpha (α) = 0.621273
   Pupil weight: 62.13%
   Iris weight: 37.87%
--------------------------------------------------------------------------------

[2/2] Starting Flask API server...
--------------------------------------------------------------------------------
   Host: 0.0.0.0
   Port: 5000
   Debug: False
   Max file size: 16MB
============================================================================

🚀 Server ready! API endpoints:
   - GET  http://0.0.0.0:5000/health - Health check
   - GET  http://0.0.0.0:5000/model/info - Model information
   - POST http://0.0.0.0:5000/predict - Single image prediction
   - POST http://0.0.0.0:5000/predict/batch - Batch prediction
============================================================================

 * Running on all addresses (0.0.0.0)
 * Running on http://127.0.0.1:5000
```

**Test it:**

Open another terminal and run:

```powershell
# Test health endpoint
curl http://localhost:5000/health
```

Expected response:
```json
{
  "status": "healthy",
  "model_loaded": true,
  "version": "1.0.0"
}
```

✅ **Flask Backend is now running!** Keep this terminal open.

---

### **PART 2: Node.js Backend Setup (API Server)**

#### **Step 2.1: Open New Terminal**

Open a **new PowerShell terminal** (keep Flask running in the first one).

#### **Step 2.2: Navigate to Node.js Backend**

```powershell
cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\eye-glaze-server-main"
```

#### **Step 2.3: Install Node.js Dependencies**

```powershell
npm install
```

**This will install (~200MB):**
- express==5.1.0
- mongodb==6.19.0
- cloudinary==2.7.0
- @google/genai==1.24.0
- cors==2.8.5
- And more...

**Installation time:** 2-5 minutes.

#### **Step 2.4: Configure Node.js Environment**

Check if `.env` file exists:

```powershell
cat .env
```

**Required `.env` configuration:**

```properties
EXPRESS_PORT = 5174
EXPRESS_MONGO_NODE_SRV = mongodb+srv://johnmike516201:yVhMgKoHxUvpJWnb@cluster0.ztb7u.mongodb.net/
CLOUDINARY_CLOUD_NAME = dhqfhnnam
CLOUDINARY_API_KEY = 459925933423651
CLOUDINARY_API_SECRET = I8ywBW0xd0KZoGhwgFpAP7hjUv4
GEMINI_API_KEY = AIzaSyDWVyccFAZCaZi3RsHzP6nHwLOC43DNhpI
```

**⚠️ IMPORTANT:** 
- These are the actual credentials from your project
- For production, use environment-specific credentials
- Never commit `.env` files to public repositories

#### **Step 2.5: Test MongoDB Connection**

```powershell
# Start Node.js server (keep this terminal open)
npm run dev
```

**Expected output:**
```
> server-1@1.0.0 dev
> nodemon index.js

[nodemon] starting `node index.js`
Server running on port: http://localhost:5174
MongoDB Connection Status: http://localhost:5174/api/status/db
```

**Test it:**

Open another terminal and run:

```powershell
# Test health endpoint
curl http://localhost:5174/api/health
```

Expected response:
```json
{
  "status": "operational",
  "timestamp": "2025-11-01T...",
  "serverInfo": { ... },
  "database": {
    "connected": true,
    "name": "eye-glaze-db"
  }
}
```

**Test database connection:**

```powershell
curl http://localhost:5174/api/status/db
```

Expected response:
```json
{
  "status": "success",
  "message": "Connected to MongoDB",
  "connectionState": "connected"
}
```

✅ **Node.js Backend is now running!** Keep this terminal open.

---

### **PART 3: React Frontend Setup (Web Interface)**

#### **Step 3.1: Open New Terminal**

Open a **third PowerShell terminal** (keep Flask and Node.js running).

#### **Step 3.2: Navigate to React Frontend**

```powershell
cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\eye-glaze-client-react-vite-main"
```

#### **Step 3.3: Install React Dependencies**

```powershell
npm install
```

**This will install (~300MB):**
- react==18.3.1
- typescript==5.5.3
- vite==5.4.8
- tailwindcss==3.4.13
- @radix-ui/* (shadcn/ui components)
- And 500+ more packages...

**Installation time:** 3-7 minutes.

#### **Step 3.4: Start React Development Server**

```powershell
npm run dev
```

**Expected output:**
```
> vite-react-typescript-starter@0.0.0 dev
> vite

  VITE v5.4.8  ready in 1234 ms

  ➜  Local:   http://localhost:5173/
  ➜  Network: use --host to expose
  ➜  press h + enter to show help
```

#### **Step 3.5: Open in Browser**

The app should automatically open in your browser. If not:

```
http://localhost:5173
```

✅ **React Frontend is now running!** Keep this terminal open.

---

## 🎉 All Services Running!

You should now have **3 terminals open**:

| Terminal | Service | Port | Status |
|----------|---------|------|--------|
| **Terminal 1** | 🔬 Flask Backend | 5000 | Running |
| **Terminal 2** | ⚙️ Node.js Backend | 5174 | Running |
| **Terminal 3** | 🎨 React Frontend | 5173 | Running |

---

## 🔗 Access Points

### **Main Application:**
- **Web App**: http://localhost:5173

### **API Endpoints:**

#### Flask Backend (Port 5000):
- Health: http://localhost:5000/health
- Model Info: http://localhost:5000/model/info
- Predict: POST http://localhost:5000/predict

#### Node.js Backend (Port 5174):
- Health: http://localhost:5174/api/health
- DB Status: http://localhost:5174/api/status/db
- Auth: http://localhost:5174/api/auth/*
- Analysis: http://localhost:5174/api/analysis/*
- Upload: http://localhost:5174/api/upload/*
- Recommendations: http://localhost:5174/api/recommendations/*

---

## 🧪 Testing the System

### **Step 1: Register a User**

1. Open http://localhost:5173
2. Click "Register" or go to http://localhost:5173/register
3. Create an account with:
   - Username/Email
   - Password
4. Click "Register"

### **Step 2: Login**

1. Go to http://localhost:5173/login
2. Enter your credentials
3. You'll be redirected to the Dashboard

### **Step 3: Upload Eye Image**

1. Go to Dashboard: http://localhost:5173/dashboard
2. Drag & drop an eye image or click to select
3. Click "Analyze Image"
4. Wait for results (~2-5 seconds)

### **Step 4: View Results**

You should see:
- ✅ Stress level (High Stress / Normal)
- ✅ Stress probability percentage
- ✅ Confidence level
- ✅ Pupil detection info
- ✅ Model interpretation (alpha weights)

### **Step 5: View History**

1. Go to Results page: http://localhost:5173/results
2. See all your previous analyses
3. Get AI-powered recommendations

---

## 🛑 Stopping Services

To stop any service:

1. Go to the terminal running that service
2. Press `Ctrl + C`
3. Confirm if prompted

**To stop all services:**
- Close all 3 terminal windows, OR
- Press `Ctrl + C` in each terminal

---

## 🔄 Restarting Services

### **Daily Development Workflow:**

**Terminal 1 - Flask:**
```powershell
cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\flask_backend"
.\.venv311\Scripts\Activate.ps1
python app.py
```

**Terminal 2 - Node.js:**
```powershell
cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\eye-glaze-server-main"
npm run dev
```

**Terminal 3 - React:**
```powershell
cd "G:\Iris_Stress_Detector\Full System\Final_project\Final_project\eye-glaze-client-react-vite-main"
npm run dev
```

---

## 🔧 Troubleshooting

### **Issue 1: Flask - Module Not Found**

```
ModuleNotFoundError: No module named 'tensorflow'
```

**Solution:**
```powershell
cd flask_backend
.\.venv311\Scripts\Activate.ps1
pip install -r requirements.txt
```

### **Issue 2: Flask - Virtual Environment Not Activating**

```
.\.venv311\Scripts\Activate.ps1 : cannot be loaded because running scripts is disabled
```

**Solution:**
```powershell
# Run as Administrator
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### **Issue 3: Node.js - MongoDB Connection Failed**

```
Error: connect ECONNREFUSED
```

**Solution:**
- Check internet connection (MongoDB Atlas is cloud-based)
- Verify `.env` has correct MongoDB connection string
- Check MongoDB Atlas whitelist (allow all IPs: 0.0.0.0/0)

### **Issue 4: Node.js - Module Not Found**

```
Error: Cannot find module 'express'
```

**Solution:**
```powershell
cd eye-glaze-server-main
npm install
```

### **Issue 5: React - Port Already in Use**

```
Port 5173 is in use, trying another one...
```

**Solution:**
```powershell
# Kill process on port 5173
netstat -ano | findstr :5173
taskkill /PID <process_id> /F

# Or use the suggested port (e.g., 5174)
```

### **Issue 6: React - Dependencies Not Installed**

```
Error: Cannot find module '@radix-ui/react-avatar'
```

**Solution:**
```powershell
cd eye-glaze-client-react-vite-main
npm install
```

### **Issue 7: CORS Error in Browser**

```
Access to fetch at 'http://localhost:5000/predict' blocked by CORS
```

**Solution:**
- Check Flask `.env` has correct CORS_ORIGINS
- Restart Flask backend after changing `.env`

### **Issue 8: Model Not Loading**

```
FileNotFoundError: Model file not found
```

**Solution:**
```powershell
# Verify model exists
Test-Path flask_backend\Model\best_dual_stream_model.keras

# If not, copy model file to the correct location
```

---

## 📊 Port Reference

| Port | Service | URL |
|------|---------|-----|
| 5000 | Flask Backend | http://localhost:5000 |
| 5174 | Node.js Backend | http://localhost:5174 |
| 5173 | React Frontend | http://localhost:5173 |

**Make sure no other applications are using these ports!**

To check:
```powershell
netstat -ano | findstr :5000
netstat -ano | findstr :5174
netstat -ano | findstr :5173
```

---

## 💡 Development Tips

### **1. Auto-Reload:**

- ✅ **React**: Auto-reloads on file save (Vite HMR)
- ✅ **Node.js**: Auto-restarts on file save (nodemon)
- ❌ **Flask**: Manual restart required (Ctrl+C, then `python app.py`)

### **2. Viewing Logs:**

Each terminal shows logs for its service:
- **Terminal 1**: Flask predictions, model loading, errors
- **Terminal 2**: API requests, database operations, errors
- **Terminal 3**: React component rendering, build info

### **3. Environment Variables:**

After changing `.env` files:
- Stop the service (Ctrl+C)
- Restart the service

### **4. Database Changes:**

MongoDB changes are instant - no restart needed.

### **5. Hot Module Replacement (HMR):**

React supports HMR - changes appear instantly without full reload!

---

## 📦 Dependencies Summary

### **Flask Backend:**
- **Size**: ~800MB
- **Packages**: 47
- **Install Time**: 5-10 minutes
- **Key Packages**: TensorFlow, Flask, OpenCV, NumPy

### **Node.js Backend:**
- **Size**: ~200MB
- **Packages**: 10 direct + dependencies
- **Install Time**: 2-5 minutes
- **Key Packages**: Express, MongoDB, Cloudinary, Gemini

### **React Frontend:**
- **Size**: ~300MB
- **Packages**: 500+ (including all dependencies)
- **Install Time**: 3-7 minutes
- **Key Packages**: React, TypeScript, Vite, Tailwind, Radix UI

**Total Size**: ~1.3GB  
**Total Install Time**: ~15 minutes

---

## 🎯 Quick Reference

### **First-Time Setup:**

```powershell
# Terminal 1 - Flask
cd flask_backend
python -m venv .venv311
.\.venv311\Scripts\Activate.ps1
pip install -r requirements.txt
python app.py

# Terminal 2 - Node.js
cd eye-glaze-server-main
npm install
npm run dev

# Terminal 3 - React
cd eye-glaze-client-react-vite-main
npm install
npm run dev
```

### **Daily Development:**

```powershell
# Terminal 1 - Flask
cd flask_backend
.\.venv311\Scripts\Activate.ps1
python app.py

# Terminal 2 - Node.js
cd eye-glaze-server-main
npm run dev

# Terminal 3 - React
cd eye-glaze-client-react-vite-main
npm run dev
```

---

## ✅ Checklist

Before starting development, ensure:

- [ ] Python 3.8-3.11 installed
- [ ] Node.js 16+ installed
- [ ] npm installed
- [ ] Flask virtual environment created
- [ ] Flask dependencies installed
- [ ] Flask model file exists
- [ ] Flask `.env` configured
- [ ] Node.js dependencies installed
- [ ] Node.js `.env` configured (MongoDB, Cloudinary, Gemini)
- [ ] React dependencies installed
- [ ] Internet connection (for MongoDB Atlas)

---

## 🔒 Security Notes

### **Current Implementation:**
- ⚠️ Basic authentication (username + password)
- ⚠️ No password hashing
- ⚠️ No JWT tokens
- ⚠️ Development environment only

### **For Production:**
- ✅ Add password hashing (bcrypt)
- ✅ Implement JWT authentication
- ✅ Add rate limiting
- ✅ Enable HTTPS
- ✅ Secure environment variables
- ✅ Add input validation
- ✅ Configure CORS properly
- ✅ Add API authentication

---

## 📚 Additional Documentation

- **Flask Backend**: `flask_backend/README.md`
- **Node.js Backend**: `eye-glaze-server-main/README.md`
- **Integration Details**: `INTEGRATION_COMPLETE.md`
- **Model Documentation**: `../../Project_Docs/2_TRAINED_MODEL_DOCUMENTATION.md`
- **Notebook Guide**: `../../Project_Docs/1_NOTEBOOK_WORKFLOW_GUIDE.md`

---

## 🆘 Getting Help

### **Common Issues:**
1. Check terminal output for error messages
2. Verify all services are running
3. Check port conflicts
4. Verify environment variables
5. Ensure internet connection (MongoDB Atlas)

### **Still Having Issues?**
- Check error logs in each terminal
- Verify all dependencies installed
- Restart services
- Clear browser cache
- Try different browser

---

## 🎉 Success!

If you see:
- ✅ Flask: "Model loaded successfully!"
- ✅ Node.js: "Connected to MongoDB"
- ✅ React: "Local: http://localhost:5173/"

**You're ready to develop!** 🚀

Open http://localhost:5173 and start building!

---

**Last Updated:** November 1, 2025  
**Version:** 1.0.0  
**Status:** ✅ Production Ready
