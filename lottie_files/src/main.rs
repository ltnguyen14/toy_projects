use std::fs;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
struct Animation {
    v: String, // version    
    nm: String, // name
    fr: f64, // frame rate
    ip: u32, // start keyframe
    op: f64, // end keyframe
    w: u32, // animation width
    h: u32, // animation height
    assets: Vec<Asset>,
    layers: Vec<Layer>,
}

#[derive(Serialize, Deserialize)]
struct Asset {
    id: String,
    w: u32,
    h: u32,
    p: String,
}

#[derive(Serialize, Deserialize)]
struct Layer {
    nm: String,
    refId: Option<String>,
    ind: u32,
    ip: u32,
    op: u32,
    st: u32,
    ty: u32,
}

fn main() {
    let data = fs::read_to_string("example.json").expect("Cannot parse file.");
    let anim: Animation = serde_json::from_str(&data).expect("Cannot parse to Animation struct."); 

    // Header
    println!("Header data:");
    println!("  Version: {}", anim.v);
    println!("  Name: {}", anim.nm);
    println!("  Frame Rate: {}", anim.fr);
    println!("  Start Keyframe: {}", anim.ip);
    println!("  End Keyframe: {}", anim.op);
    println!("  Animation Width: {}", anim.w);
    println!("  Animation Height: {}", anim.h);

    // Assets
    for asset in anim.assets {
        println!("Asset id: {}", asset.id);
        println!("  Asset width: {}", asset.w);
        println!("  Asset height: {}", asset.h);
        println!("  Asset name: {}", asset.p);
    }

    // Layers
    for mut layer in anim.layers {
        println!("Layer name: {}", layer.nm);
        println!("  Layer type: {}", layer.ty);
        println!("  Layer resource id: {}", layer.refId.get_or_insert(String::from("--")));
        println!("  Layer id: {}", layer.ind);
        println!("  Layer start keyframe: {}", layer.ip);
        println!("  Layer end keyframe: {}", layer.op);
        println!("  Layer start time: {}", layer.st);
    }
}
