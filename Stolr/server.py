from flask import Flask, render_template, session, redirect, url_for, request, flash
from flask_session import Session
import sqlite3
import os
import json
from datetime import datetime
app = Flask(__name__, static_folder="public")
app.secret_key = "parolamea123"
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class Order(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    items = db.Column(db.Text)  # json cu produse
    total_price = db.Column(db.Float)  # total plata
    timestamp = db.Column(db.DateTime, default=db.func.current_timestamp())  # cand s-a facut comanda

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///orders.db'  # baza de date sqlite
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db.init_app(app)


# functii pentru baza de date cu scaune
def get_db_connection():
    conn = sqlite3.connect('chairs.db')  # conecteaza la db
    conn.row_factory = sqlite3.Row  # ca sa fie mai usor de folosit
    return conn

# ia toate scaunele intre preturi
def load_chairs(min_price=0, max_price=99999):
    conn = get_db_connection()
    query = "SELECT * FROM chairs WHERE price BETWEEN ? AND ?"  # query simplu
    chairs = conn.execute(query, (min_price, max_price)).fetchall()
    conn.close()  # inchide conexiunea
    return chairs

# ia un singur scaun
def get_chair_by_id(chair_id):
    conn = get_db_connection()
    chair = conn.execute("SELECT * FROM chairs WHERE id = ?", (chair_id,)).fetchone()
    conn.close()
    return chair  # sau None daca nu exista

# ia cosul din sesiune
def get_cart():
    cart = session.get("cart")
    if not isinstance(cart, dict):  # daca nu e dict, fa-l dict gol
        cart = {}
    return cart

# salveaza cosul in sesiune
def save_cart(cart):
    session["cart"] = cart  # simplu

@app.route("/")
def index():
    # filtre preturi
    try:
        min_price = int(request.args.get("min_price", "").strip() or 0)
    except ValueError:
        min_price = 0  # default daca crapa
    try:
        max_price = int(request.args.get("max_price", "").strip() or 99999)
    except ValueError:
        max_price = 99999  # default

    chairs = load_chairs(min_price, max_price)
    return render_template("index.html", chairs=chairs, cart=get_cart())

# adauga in cos
@app.route("/add/<int:id>")
def add_item(id):
    cart = get_cart()
    id_str = str(id)  # string ca sa fie cheie in dict

    if id_str in cart:
        cart[id_str]["quantity"] += 1  # creste cantitatea
    else:
        chair = get_chair_by_id(id)
        if chair:  # daca scaunul exista
            cart[id_str] = {
                "id": chair["id"],
                "name": chair["name"],
                "description": chair["description"],
                "price": chair["price"],
                "quantity": 1  # prima data
            }

    save_cart(cart)
    return redirect(url_for("index"))  # inapoi la produse


@app.route('/cart')
def cart():
    cart = get_cart()
    total = sum(item['price'] * item['quantity'] for item in cart.values())  # calculeaza total
    return render_template("cart.html", cart=cart, total=total)

# sterge din cos
@app.route("/remove/<int:id>")
def remove_item(id):
    cart = get_cart()
    cart.pop(str(id), None)  # sterge daca exista
    save_cart(cart)
    return redirect(url_for("cart"))

# update cantitate
@app.route("/update_quantity/<int:id>", methods=["POST"])
def update_quantity(id):
    quantity = int(request.form.get("quantity", 1))  # ia cantitatea din form
    cart = get_cart()
    if str(id) in cart:
        if quantity > 0:
            cart[str(id)]["quantity"] = quantity  # update
        else:
            cart.pop(str(id), None)  # sterge daca cant=0
    save_cart(cart)
    return redirect(url_for("cart"))

# pagina produs
@app.route("/product/<int:id>")
def product_page(id):
    chair = get_chair_by_id(id)
    if not chair:
        return "Chair not found", 404  # 404 daca nu exista
    return render_template("product.html", chair=chair)

# injecteaza cosul in toate template-urile
@app.context_processor
def inject_cart():
    return dict(cart=get_cart())

# checkout
@app.route("/checkout", methods=["GET", "POST"])
def checkout():
    cart = get_cart()
    
    if not cart:
        flash("Your cart is empty!", "warning")  # mesaj daca cos gol
        return redirect(url_for("cart"))
    
    if request.method == "POST":
        # colecteaza datele
        order_data = {
            "full_name": request.form.get("full_name"),
            "email": request.form.get("email"),
            "phone": request.form.get("phone"),
            "address": request.form.get("address"),
            "payment_method": request.form.get("payment_method"),
            "cart": cart,
            "total": sum(item["price"] * item["quantity"] for item in cart.values()),
            "timestamp": datetime.now().isoformat()  # cand s-a plasat
        }

        # salveaza comanda ca json
        os.makedirs("submitted-data", exist_ok=True)  # folder daca nu exista
        filename = f"submitted-data/order_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json"
        with open(filename, "w") as f:
            json.dump(order_data, f, indent=2)  # salveaza frumos

        # salveaza in db
        order = Order(
            items=json.dumps(cart),
            total_price=order_data["total"]
        )
        db.session.add(order)
        db.session.commit()

        session.pop("cart", None)  # gol cos
        flash("Order placed successfully!", "success")  # mesaj succes
        return render_template("checkout_success.html", order=order_data)
    else:
        total = sum(item["price"] * item["quantity"] for item in cart.values())
        return render_template("checkout.html", cart=cart, total=total)
    
@app.route("/contact")
def contact():
    return render_template("contact.html")

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)