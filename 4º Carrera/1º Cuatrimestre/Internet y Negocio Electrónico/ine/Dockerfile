FROM php:8.2-fpm

RUN apt-get update && apt-get install -y \
  git unzip zip libzip-dev libpng-dev libonig-dev libxml2-dev \
  && docker-php-ext-install pdo_mysql mbstring zip exif pcntl bcmath gd

COPY --from=composer:2 /usr/bin/composer /usr/bin/composer

WORKDIR /var/www/html

COPY . .

# Crear directorios necesarios para que no fallen los comandos chown
RUN mkdir -p /var/www/html/storage /var/www/html/bootstrap/cache

# Cambiar propietarios de los directorios
RUN chown -R www-data:www-data /var/www/html/storage /var/www/html/bootstrap/cache

EXPOSE 9000

CMD ["php-fpm"]
