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
🚀 Local Development & TestingThe project is fully Dockerized. You can launch the entire stack (Frontend + Backend) with a single command — no need to install Java or Node.js locally.📋 PrerequisitesDockerDocker ComposeGit🛠️ Quick Start1️⃣ Clone the repository (including submodules)Bashgit clone --recursive [https://github.com/Huyhuy225/AFES.git](https://github.com/Huyhuy225/AFES.git) 
cd AFES
2️⃣ Spin up the systemBashdocker-compose up --build
3️⃣ Access the servicesFrontend Dashboard: http://localhostBackend API: http://localhost:8080Swagger UI (API Docs): http://localhost:8080/swagger-ui/index.html🌐 Live DeploymentThe system is deployed using a hybrid cloud strategy for maximum regional availability and efficiency.ComponentStatusHosting ProviderLive URLFrontendLiveGitHub Pageshttps://huyhuy225.github.io/afes_FE/BackendLiveAzure Container AppsAPI Endpoint🛠️ Tech Stack🎨 FrontendReact.jsViteTailwind CSSAxiosChart.js⚙️ BackendJava 17+Spring Boot 3.xSpring Data JPAHibernate☁️ InfrastructureAzure Container Apps (Southeast Asia region)🔁 DevOpsDockerDocker ComposeGitHub Actions (CI/CD)🔧 Configuration & Security1️⃣ CORS ManagementThe Backend strictly allows requests only from trusted origins:http://localhost (Development)https://huyhuy225.github.io (Production)2️⃣ Environment VariablesFrontend: VITE_API_URL → Points to the correct Backend endpoint depending on the environment.Backend: Database credentials, API ports (All managed via Docker environment variables).3️⃣ CI/CD PipelineEvery push to the main branch automatically:Builds production assetsDeploys the Frontend to GitHub Pages(Fully automated via GitHub Actions).👤 AuthorHuy VoGitHub: @Huyhuy225Role: Fullstack Developer & DevOps Engineer
