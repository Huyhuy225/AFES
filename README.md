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

## ☸️ Kubernetes Deployment (Minikube)

For production-grade orchestration, the system can be deployed to a Kubernetes cluster.

### 🚀 Deployment Order
Execute these commands in the following sequence to ensure all dependencies are resolved:

```bash
# 1. Prepare Environment
kubectl apply -f k8s/namespace.yaml

# 2. Configuration & Infrastructure
kubectl apply -f k8s/configmap.yaml
kubectl apply -f k8s/secret.yaml
kubectl apply -f k8s/mysql-pvc.yaml

# 3. Databases & Services
kubectl apply -f k8s/mysql-deployment.yaml
kubectl apply -f k8s/mosquitto-deployment.yaml

# 4. Applications
kubectl apply -f k8s/backend-deployment.yaml
kubectl apply -f k8s/frontend-deployment.yaml
```

### 🔍 Verification
Check the status of all resources in the `afes` namespace:
```bash
kubectl get all -n afes
```

Access the frontend dashboard via Minikube:
```bash
minikube service frontend-service -n afes
```

---

## ☁️ Azure Deployment (AKS)

To deploy the system to Azure Kubernetes Service (AKS), follow these steps:

### 🚀 Prerequisites
- [Azure CLI](https://learn.microsoft.com/en-us/cli/azure/install-azure-cli) installed.
- An active Azure Subscription.

### 🛠️ Step-by-Step

```bash
# 1. Login & Setup
az login
az account set --subscription d94f5a82-3d38-4f3e-85c5-548c90ed2d81--generate-ssh-keys

# 2. Connect kubectl to AKS
az aks get-credentials --resource-group AFES_Group --name afes_cluster --overwrite-existing

# 3. Build & Push Images (Docker Hub example)
docker build -t huyhuy225/afes-backend:latest ./backend
docker push huyhuy225/afes-backend:latest
docker build -t huyhuy225/afes-frontend:latest ./frontend
docker push huyhuy225/afes-frontend:latest

# 4. Deploy Manifests
kubectl apply -f k8s/
kubectl rollout restart deployment/frontend -n afes
```

### 🌐 Accessing the App
Get the external IP of the frontend service:
```bash
kubectl get svc frontend-service -n afes
kubectl get pods -n afes
kubectl logs --tail=100 -n afes <pod-name>
```

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

