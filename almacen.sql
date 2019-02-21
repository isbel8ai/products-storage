CREATE TABLE producto (
  id            INTEGER NOT NULL, 
  nombre       varchar(255) NOT NULL, 
  codigo       varchar(255) NOT NULL UNIQUE, 
  descripcion  varchar(255) NOT NULL, 
  costo_actual double NOT NULL, 
  PRIMARY KEY (id));
CREATE TABLE tienda (
  id           INTEGER NOT NULL, 
  nombre      varchar(255) NOT NULL UNIQUE, 
  descripcion varchar(255) NOT NULL, 
  PRIMARY KEY (id));
CREATE TABLE venta (
  id          INTEGER NOT NULL, 
  cantidad   integer NOT NULL, 
  descontado integer NOT NULL, 
  loteid     integer NOT NULL, 
  facturaid  integer NOT NULL, 
  PRIMARY KEY (id), 
  FOREIGN KEY(facturaid) REFERENCES factura(id), 
  FOREIGN KEY(loteid) REFERENCES lote(id));
CREATE TABLE lote (
  id          INTEGER NOT NULL, 
  precio     double NOT NULL, 
  existencia integer NOT NULL, 
  tiendaid   integer NOT NULL, 
  depositoid integer NOT NULL, 
  PRIMARY KEY (id), 
  FOREIGN KEY(tiendaid) REFERENCES tienda(id), 
  FOREIGN KEY(depositoid) REFERENCES deposito(id));
CREATE TABLE salida (
  id          INTEGER NOT NULL, 
  fecha      integer NOT NULL, 
  cantidad   integer NOT NULL, 
  depositoid integer NOT NULL, 
  loteid     integer NOT NULL, 
  PRIMARY KEY (id), 
  FOREIGN KEY(depositoid) REFERENCES deposito(id), 
  FOREIGN KEY(loteid) REFERENCES lote(id));
CREATE TABLE entrada (
  id          INTEGER NOT NULL, 
  fecha      date NOT NULL, 
  cantidad   integer NOT NULL, 
  depositoid integer NOT NULL, 
  PRIMARY KEY (id), 
  FOREIGN KEY(depositoid) REFERENCES deposito(id));
CREATE TABLE factura (
  id         INTEGER NOT NULL, 
  fecha     date NOT NULL, 
  descuento double NOT NULL, 
  tiendaid  integer NOT NULL, 
  PRIMARY KEY (id), 
  FOREIGN KEY(tiendaid) REFERENCES tienda(id));
CREATE TABLE deposito (
  id             INTEGER NOT NULL, 
  costo         double NOT NULL, 
  existencia    integer NOT NULL, 
  productoid    integer NOT NULL, 
  precio_actual double NOT NULL, 
  PRIMARY KEY (id), 
  FOREIGN KEY(productoid) REFERENCES producto(id));
