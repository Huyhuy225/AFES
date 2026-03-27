# 🛡️ AFES - Advanced Fire Emergency System

AFES is a professional real-time fire monitoring and alert dashboard. It leverages IoT sensor data (temperature, smoke, etc.) to provide instant safety status updates and emergency notifications.

The system architecture follows a modern Fullstack approach with a fully decoupled Frontend and Backend.

## 🏗️ System Architecture

This repository acts as the master orchestrator, managing the entire lifecycle of the AFES project through containerization.

```text
AFES/ 
├── frontend/           # React + Vite (Dashboard UI) 
├── backend/            # Java Spring Boot (REST API & Business Logic) 
├── docker-compose.yml 
└── README.md
```

## 🚀 Local Development & Testing

The project is fully Dockerized. You can launch the entire stack (Frontend + Backend) with a single command — no need to install Java or Node.js locally.

### 📋 Prerequisites

- Docker
- Docker Compose
- Git

---

## 🛠️ Quick Start

### 1️⃣ Clone the repository (including submodules)

```bash
git clone --recursive https://github.com/Huyhuy225/AFES.git
cd AFES
```
### 2️⃣ Spin up the system
```bash
docker-compose up --build
```
### 3️⃣ Access the services
- Frontend Dashboard: http://localhost
- Backend API: http://localhost:8080
- Swagger UI (API Docs): http://localhost:8080/swagger-ui/index.html

## 🌐 Live Deployment

The system is deployed using a hybrid cloud strategy for maximum regional availability and efficiency.

| Component | Status | Hosting Provider | Live URL |
| --- | --- | --- | --- |
| **Frontend** | Live | GitHub Pages | [https://huyhuy225.github.io/afes_FE/](https://huyhuy225.github.io/afes_FE/) |
| **Backend** | Live | Azure Container Apps | *API Endpoint* |

## 🛠️ Tech Stack

### 🎨 Frontend
* React.js
* Vite
* Tailwind CSS
* Axios
* Chart.js

### ⚙️ Backend
* Java 17+
* Spring Boot 3.x
* Spring Data JPA
* Hibernate

### ☁️ Infrastructure
* Azure Container Apps (Southeast Asia region)

### 🔁 DevOps
* Docker
* Docker Compose
* GitHub Actions (CI/CD)

---

## 🔧 Configuration & Security

### 1️⃣ CORS Management
The Backend strictly allows requests only from trusted origins:
* `http://localhost` (Development)
* `[https://huyhuy225.github.io/afes_FE/](https://huyhuy225.github.io/afes_FE/)` (Production)

### 2️⃣ Environment Variables

**Frontend**
* `VITE_API_URL` → Points to the correct Backend endpoint depending on the environment.

**Backend**
* Database credentials
* API ports
*(All managed via Docker environment variables).*

### 3️⃣ CI/CD Pipeline
Every push to the main branch automatically:
* Builds production assets
* Deploys the Frontend to GitHub Pages

> *Fully automated via GitHub Actions.*

---

## 👤 Author

**Vo Quang Huy**
* **GitHub:** [https://github.com/Huyhuy225](https://github.com/Huyhuy225)

**Ho Cong Thanh**
* **GitHub:** [https://github.com/thanhhocong](https://github.com/thanhhocong)

**Nguyen Hieu Trung**
* **GitHub:** [https://github.com/nghitrung](https://github.com/nghitrung)

**Tran Thanh Nhu Y**
* **GitHub:** [https://github.com/gutjmosnin](https://github.com/gutjmosnin)

