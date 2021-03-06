--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: formaciones; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.formaciones (
    "idFormacion" integer NOT NULL,
    formacion character varying(15) NOT NULL,
    descripcion character varying(150) NOT NULL
);


ALTER TABLE public.formaciones OWNER TO postgres;

--
-- Name: formaciones_idFormacion_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."formaciones_idFormacion_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."formaciones_idFormacion_seq" OWNER TO postgres;

--
-- Name: formaciones_idFormacion_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."formaciones_idFormacion_seq" OWNED BY public.formaciones."idFormacion";


--
-- Name: idQuinteto_idFormaciones; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."idQuinteto_idFormaciones" (
    "idQuinteto_titular" integer NOT NULL,
    "idFormaciones" integer NOT NULL
);


ALTER TABLE public."idQuinteto_idFormaciones" OWNER TO postgres;

--
-- Name: idQuinteto_idFormaciones_idFormaciones_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."idQuinteto_idFormaciones_idFormaciones_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."idQuinteto_idFormaciones_idFormaciones_seq" OWNER TO postgres;

--
-- Name: idQuinteto_idFormaciones_idFormaciones_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."idQuinteto_idFormaciones_idFormaciones_seq" OWNED BY public."idQuinteto_idFormaciones"."idFormaciones";


--
-- Name: idQuinteto_idFormaciones_idQuinteto_titular_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."idQuinteto_idFormaciones_idQuinteto_titular_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."idQuinteto_idFormaciones_idQuinteto_titular_seq" OWNER TO postgres;

--
-- Name: idQuinteto_idFormaciones_idQuinteto_titular_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."idQuinteto_idFormaciones_idQuinteto_titular_seq" OWNED BY public."idQuinteto_idFormaciones"."idQuinteto_titular";


--
-- Name: jugadores; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.jugadores (
    idjugadores integer NOT NULL,
    nombre character varying(18) NOT NULL,
    apellidos character varying(35) NOT NULL,
    dorsal integer NOT NULL,
    posicion integer NOT NULL,
    puntos_partido double precision,
    asist_partido double precision,
    reb_partido double precision,
    faltas_partido double precision,
    robos_partido double precision,
    min_partido double precision,
    anyo_nac integer,
    nacionalidad character varying(25),
    altura double precision,
    peso double precision,
    email character varying(30) NOT NULL,
    dni character varying(9) NOT NULL,
    idusuario integer
);


ALTER TABLE public.jugadores OWNER TO postgres;

--
-- Name: jugadores_idJugadores_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."jugadores_idJugadores_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."jugadores_idJugadores_seq" OWNER TO postgres;

--
-- Name: jugadores_idJugadores_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."jugadores_idJugadores_seq" OWNED BY public.jugadores.idjugadores;


--
-- Name: quinteto_titular; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.quinteto_titular (
    "idQuinteto_titular" integer NOT NULL,
    "idJugadores" integer NOT NULL
);


ALTER TABLE public.quinteto_titular OWNER TO postgres;

--
-- Name: quinteto_titular_idJugadores_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."quinteto_titular_idJugadores_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."quinteto_titular_idJugadores_seq" OWNER TO postgres;

--
-- Name: quinteto_titular_idJugadores_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."quinteto_titular_idJugadores_seq" OWNED BY public.quinteto_titular."idJugadores";


--
-- Name: quinteto_titular_idQuinteto_titular_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."quinteto_titular_idQuinteto_titular_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."quinteto_titular_idQuinteto_titular_seq" OWNER TO postgres;

--
-- Name: quinteto_titular_idQuinteto_titular_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."quinteto_titular_idQuinteto_titular_seq" OWNED BY public.quinteto_titular."idQuinteto_titular";


--
-- Name: staff; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.staff (
    "idStaff" integer NOT NULL,
    nombre character varying(18) NOT NULL,
    apellidos character varying(35) NOT NULL,
    email character varying(40) NOT NULL,
    telefono integer NOT NULL,
    anyo_nac integer NOT NULL,
    cargo character varying(150) NOT NULL
);


ALTER TABLE public.staff OWNER TO postgres;

--
-- Name: staff_idStaff_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."staff_idStaff_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."staff_idStaff_seq" OWNER TO postgres;

--
-- Name: staff_idStaff_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."staff_idStaff_seq" OWNED BY public.staff."idStaff";


--
-- Name: usuarios; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.usuarios (
    idusuario integer NOT NULL,
    usuario character varying(20) NOT NULL,
    pass text NOT NULL
);


ALTER TABLE public.usuarios OWNER TO postgres;

--
-- Name: usuarios_idUsuario_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."usuarios_idUsuario_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."usuarios_idUsuario_seq" OWNER TO postgres;

--
-- Name: usuarios_idUsuario_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."usuarios_idUsuario_seq" OWNED BY public.usuarios.idusuario;


--
-- Name: formaciones idFormacion; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.formaciones ALTER COLUMN "idFormacion" SET DEFAULT nextval('public."formaciones_idFormacion_seq"'::regclass);


--
-- Name: idQuinteto_idFormaciones idQuinteto_titular; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."idQuinteto_idFormaciones" ALTER COLUMN "idQuinteto_titular" SET DEFAULT nextval('public."idQuinteto_idFormaciones_idQuinteto_titular_seq"'::regclass);


--
-- Name: idQuinteto_idFormaciones idFormaciones; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."idQuinteto_idFormaciones" ALTER COLUMN "idFormaciones" SET DEFAULT nextval('public."idQuinteto_idFormaciones_idFormaciones_seq"'::regclass);


--
-- Name: jugadores idjugadores; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.jugadores ALTER COLUMN idjugadores SET DEFAULT nextval('public."jugadores_idJugadores_seq"'::regclass);


--
-- Name: quinteto_titular idQuinteto_titular; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.quinteto_titular ALTER COLUMN "idQuinteto_titular" SET DEFAULT nextval('public."quinteto_titular_idQuinteto_titular_seq"'::regclass);


--
-- Name: quinteto_titular idJugadores; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.quinteto_titular ALTER COLUMN "idJugadores" SET DEFAULT nextval('public."quinteto_titular_idJugadores_seq"'::regclass);


--
-- Name: staff idStaff; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.staff ALTER COLUMN "idStaff" SET DEFAULT nextval('public."staff_idStaff_seq"'::regclass);


--
-- Name: usuarios idusuario; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuarios ALTER COLUMN idusuario SET DEFAULT nextval('public."usuarios_idUsuario_seq"'::regclass);


--
-- Data for Name: formaciones; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.formaciones ("idFormacion", formacion, descripcion) FROM stdin;
\.


--
-- Data for Name: idQuinteto_idFormaciones; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."idQuinteto_idFormaciones" ("idQuinteto_titular", "idFormaciones") FROM stdin;
\.


--
-- Data for Name: jugadores; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.jugadores (idjugadores, nombre, apellidos, dorsal, posicion, puntos_partido, asist_partido, reb_partido, faltas_partido, robos_partido, min_partido, anyo_nac, nacionalidad, altura, peso, email, dni, idusuario) FROM stdin;
\.


--
-- Data for Name: quinteto_titular; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.quinteto_titular ("idQuinteto_titular", "idJugadores") FROM stdin;
\.


--
-- Data for Name: staff; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.staff ("idStaff", nombre, apellidos, email, telefono, anyo_nac, cargo) FROM stdin;
\.


--
-- Data for Name: usuarios; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.usuarios (idusuario, usuario, pass) FROM stdin;
33	wismichu	$2a$06$fgj/teSARAZSnZDfE2OyZ.uTA9k.1FxSwbrGqxmiMquhaOaXU9nha
35	javi	$2a$06$3yuIqfJTOoQYjni/tm4iKufmQHYkY8NfKDDBeUkY2c/LWsRrXNbBy
\.


--
-- Name: formaciones_idFormacion_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."formaciones_idFormacion_seq"', 1, false);


--
-- Name: idQuinteto_idFormaciones_idFormaciones_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."idQuinteto_idFormaciones_idFormaciones_seq"', 1, false);


--
-- Name: idQuinteto_idFormaciones_idQuinteto_titular_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."idQuinteto_idFormaciones_idQuinteto_titular_seq"', 1, false);


--
-- Name: jugadores_idJugadores_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."jugadores_idJugadores_seq"', 61, true);


--
-- Name: quinteto_titular_idJugadores_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."quinteto_titular_idJugadores_seq"', 1, false);


--
-- Name: quinteto_titular_idQuinteto_titular_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."quinteto_titular_idQuinteto_titular_seq"', 1, false);


--
-- Name: staff_idStaff_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."staff_idStaff_seq"', 1, false);


--
-- Name: usuarios_idUsuario_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."usuarios_idUsuario_seq"', 35, true);


--
-- Name: formaciones formaciones_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.formaciones
    ADD CONSTRAINT formaciones_pkey PRIMARY KEY ("idFormacion");


--
-- Name: jugadores jugadores_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.jugadores
    ADD CONSTRAINT jugadores_pkey PRIMARY KEY (idjugadores);


--
-- Name: quinteto_titular quinteto_titular_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.quinteto_titular
    ADD CONSTRAINT quinteto_titular_pkey PRIMARY KEY ("idQuinteto_titular");


--
-- Name: staff staff_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.staff
    ADD CONSTRAINT staff_pkey PRIMARY KEY ("idStaff");


--
-- Name: usuarios usuarios_idUsuario_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuarios
    ADD CONSTRAINT "usuarios_idUsuario_key" UNIQUE (idusuario);


--
-- Name: usuarioUnico; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX "usuarioUnico" ON public.usuarios USING btree (usuario);


--
-- Name: jugadores jugadores_idUsuario_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.jugadores
    ADD CONSTRAINT "jugadores_idUsuario_fkey" FOREIGN KEY (idusuario) REFERENCES public.usuarios(idusuario);


--
-- PostgreSQL database dump complete
--

