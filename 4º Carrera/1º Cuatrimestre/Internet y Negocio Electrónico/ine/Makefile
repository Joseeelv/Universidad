# Nombre del contenedor de la app
APP_CONTAINER = laravel_app
# Inicia los contenedores en segundo plano
up:
	docker-compose up -d

# Detiene los contenedores
down:
	docker-compose down

# Reconstruye la imagen sin usar caché
build:
	docker-compose build --no-cache

restart:
	docker-compose down
	docker-compose up --build -d

# Reconstruye y levanta
rebuild: 
	down build up

# Muestra logs en tiempo real
logs:
	docker-compose logs -f

# Accede a la shell del contenedor PHP
bash:
	docker-compose exec $(APP_CONTAINER) bash

# Ejecuta un comando artisan
artisan:
	docker-compose exec $(APP_CONTAINER) php artisan $(cmd)

# Limpia cachés de Laravel
cache-clear:
	docker-compose exec $(APP_CONTAINER) php artisan cache:clear
	docker-compose exec $(APP_CONTAINER) php artisan config:clear
	docker-compose exec $(APP_CONTAINER) php artisan route:clear
	docker-compose exec $(APP_CONTAINER) php artisan view:clear

# Genera la key de Laravel
key-generate:
	docker-compose exec $(APP_CONTAINER) php artisan key:generate

# Migraciones
migrate:
	docker exec -it $(APP_CONTAINER) php artisan migrate


# Refresca migraciones
migrate-refresh:
	docker-compose exec $(APP_CONTAINER) php artisan migrate:fresh --seed

# Activa el storage link
storage-link:
	docker-compose exec $(APP_CONTAINER) php artisan storage:link

# Ejecutar el scipt sql de pruebas
sql-pruebas:
ifeq ($(OS),Windows_NT)
	@powershell -Command "Get-Content ./script_pruebas.sql | docker-compose exec -T db sh -c 'mysql --default-character-set=utf8mb4 -u root -p$$MYSQL_ROOT_PASSWORD $$MYSQL_DATABASE'"
else
	@cat ./script_pruebas.sql | docker-compose exec -T db sh -c 'mysql --default-character-set=utf8mb4 -u root -p$$MYSQL_ROOT_PASSWORD $$MYSQL_DATABASE'
endif

# Hacer migraciones, storage link y sql de pruebas
data: migrate storage-link sql-pruebas


#Que me quite el link
unlink:
	docker-compose exec $(APP_CONTAINER) php artisan storage:unlink

# Elimina todo (contenedores, volúmenes, caché)
clean:
	docker-compose down --volumes --remove-orphans
	docker system prune -f
