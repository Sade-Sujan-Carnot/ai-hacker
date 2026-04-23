# Deployment Guide - FREE Weather API

## 📤 Push to GitHub

### 1. Create GitHub Repository
1. Go to [GitHub](https://github.com/new)
2. Create new repository named `weather-app-free-api`
3. Choose "Public" (optional, for free tier)
4. Don't initialize with README (we have one)
5. Click "Create repository"

### 2. Initialize Git & Push

Open Command Prompt in project root:

```bash
# Navigate to project
cd c:\Users\CBIT\w\ai-hacker

# Initialize git (if not already done)
git init

# Add all files
git add .

# Commit
git commit -m "Initial commit: Free weather API with C++ backend and animated UI"

# Add remote (replace YOUR_USERNAME and REPO_NAME)
git remote add origin https://github.com/YOUR_USERNAME/weather-app-free-api.git

# Push to GitHub
git branch -M main
git push -u origin main
```

### 3. Verify on GitHub
Visit `https://github.com/YOUR_USERNAME/weather-app-free-api`


## 🚀 Deploy Options

### Option 1: Deploy Frontend to GitHub Pages (FREE)

Best for: Static HTML/CSS/JS

```bash
# In your repo settings:
# 1. Go to Settings → Pages
# 2. Select "main" branch as source
# 3. Save
# Your site will be at: https://YOUR_USERNAME.github.io/weather-app-free-api
```

Frontend will be live, but backend must run locally.

---

### Option 2: Deploy Backend to Railway (FREE)

Best for: C++ backend hosting

#### Setup Railway:

1. Go to [Railway.app](https://railway.app)
2. Sign up with GitHub
3. Create new project
4. Connect your GitHub repo
5. Create `Procfile` in project root:
   ```
   web: ./release/weather_server
   ```

6. Set build command in Railway dashboard:
   ```
   cd backend && mkdir build && cd build && cmake .. && cmake --build . --config Release
   ```

7. Deploy!

Backend URL: `https://your-project-name.railway.app`

---

### Option 3: Deploy to Heroku (FREE Tier Ending)

Alternative hosting with credit card (but free tier available):

1. Create [Heroku](https://heroku.com) account
2. Create `Procfile`:
   ```
   web: ./backend/release/weather_server
   ```
3. Deploy via git or Heroku CLI

---

### Option 4: Deploy Everywhere with Docker

Create `backend/Dockerfile`:

```dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    libcurl4-openssl-dev \
    libjsoncpp-dev

WORKDIR /app
COPY . .

WORKDIR /app/backend/build
RUN cmake .. && cmake --build . --config Release

EXPOSE 8080
CMD ["./weather_server"]
```

Then deploy to:
- [Railway](https://railway.app)
- [Render](https://render.com)
- [AWS EC2](https://aws.amazon.com)
- [Google Cloud Run](https://cloud.google.com/run)
- [Azure Container Instances](https://azure.microsoft.com/en-us/services/container-instances/)


## 🌐 Full Stack Deployment Example (Railway)

### Step 1: Create Procfile
```
# backend/Procfile
web: ./release/weather_server
```

### Step 2: Update Frontend (index.html)
```javascript
// Replace localhost with production URL
const BACKEND_URL = "https://your-project-name.railway.app";
```

### Step 3: Deploy Frontend to GitHub Pages
```bash
git add .
git commit -m "Update backend URL for production"
git push
```

### Step 4: Configure Railway
- Connect GitHub repo
- Set environment: Node.js
- Add build command
- Deploy

### Result:
- **Frontend**: `https://your-username.github.io/weather-app-free-api`
- **Backend**: `https://your-project-name.railway.app`


## 🔧 Environment Variables

Create `.env` file for production URLs:

```env
BACKEND_URL=https://your-backend-url.railway.app
FRONTEND_URL=https://your-username.github.io/weather-app-free-api
PORT=8080
```

Update `index.html`:
```javascript
// For production
const BACKEND_URL = process.env.BACKEND_URL || "http://localhost:8080";
```


## 📊 Deployment Comparison

| Platform | Cost | Setup | Ease | Suitable For |
|----------|------|-------|------|--------------|
| **GitHub Pages** | FREE | 2 min | Very Easy | Frontend only |
| **Railway** | FREE (with limits) | 5 min | Easy | Full stack |
| **Render** | FREE (with limits) | 5 min | Easy | Full stack |
| **Vercel** | FREE | 3 min | Very Easy | Frontend only |
| **Netlify** | FREE | 3 min | Very Easy | Frontend only |
| **AWS** | Paid | 10 min | Hard | Scalable |
| **Docker + Any Host** | Varies | 15 min | Medium | Flexible |


## 🎯 Recommended Setup for FREE

### Quick & Easy:
1. Frontend → **GitHub Pages** (2 minutes)
2. Backend → **Railway** (5 minutes)
3. Connect with environment variables

**Total time: ~7 minutes**
**Total cost: $0**


## 🚨 Important Notes

### Frontend Deployment
- GitHub Pages serves from `/repository-name` path
- Update `<base>` tag if using sub-paths
- Cache-busting for updates: `?v=1.0`

### Backend Deployment
- Cold starts may take 10-30 seconds on free tier
- Implement retry logic in frontend
- Monitor for auto-sleep on inactive plans

### CORS
Frontend and backend must be on same domain or CORS must be enabled:
```
Access-Control-Allow-Origin: https://your-frontend.com
```

### SSL/HTTPS
All modern platforms provide free HTTPS
- No additional configuration needed
- Automatically renewed


## 📱 Testing Live

After deployment:

```javascript
// Test in browser console
fetch('https://your-backend.railway.app/weather')
  .then(r => r.json())
  .then(d => console.log(d))
```

Or visit:
- Frontend: `https://your-username.github.io/weather-app-free-api`
- API Docs: `https://your-backend.railway.app/`
- Weather Data: `https://your-backend.railway.app/weather`


## 🔄 Continuous Deployment

### Auto-Deploy on Git Push
Both Railway and GitHub Pages support auto-deployment:

1. Push to main branch
2. GitHub automatically deploys frontend
3. Railway automatically builds and deploys backend

**No manual steps needed!**


## 📈 Monitoring

### Monitor Backend Health:
```bash
# Check if backend is running
curl https://your-backend.railway.app/weather
```

### Monitor Frontend:
- GitHub Pages: Automatic
- Check GitHub Actions for build status

### Monitor Performance:
- Railway dashboard shows response times
- GitHub Pages has basic analytics


## 🆘 Troubleshooting

### "Backend connection failed"
- Check backend is running: Visit `https://your-backend.railway.app/`
- Verify CORS headers are set
- Check network tab in browser DevTools

### "Port already in use"
- Railway assigns port automatically via `$PORT` env var
- Update code: `int port = getenv("PORT") ? atoi(getenv("PORT")) : 8080;`

### "Cold start too slow"
- Railway has ~10-30s cold start on free tier
- Use `Keep-Alive` requests to prevent sleep
- Upgrade to paid tier for always-on

### GitHub Pages not updating
- Wait 1-2 minutes for GitHub Actions
- Check Actions tab for build status
- Clear browser cache: `Ctrl+Shift+Del`


## 💡 Pro Tips

1. **Use CDN**: Add Cloudflare for faster frontend delivery
2. **Monitor**: Set up alerts for backend downtime
3. **Backup**: Enable GitHub releases for backups
4. **Scale**: When free tier isn't enough, upgrade easily
5. **Automate**: Use GitHub Actions for deployments

---

**You now have a production-ready weather app, completely FREE and deployed globally! 🚀**
