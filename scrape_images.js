const puppeteer = require('puppeteer');
const { JSDOM } = require('jsdom');
const fs = require('fs');

async function scrapeInstagram() {
    const folderName = "assets/images";
    const browser = await puppeteer.launch();
    const page = await browser.newPage();
    await page.goto('https://www.instagram.com/kri_ookee', { waitUntil: 'networkidle2' });

    await page.waitForFunction(() => document.querySelectorAll('img').length > 0);
    await page.screenshot({ path: 'screenshot.png' });
    let content = await page.content();
    if(!fs.existsSync(folderName)){
        fs.mkdirSync(folderName);
    }
    if(content.indexOf("Something went wrong") === 0){
        console.log("Write file to cache");
        // fs.writeFileSync("test.html",content);
    }
    else {
        console.log("We were rate limited, read file from cache");
        content = fs.readFileSync("test.html");
    }
    const {document} = new JSDOM(content).window;
    const articleNode = document.querySelector('article');
    const images = articleNode.querySelectorAll('img');

    let out_html = "<!DOCTYPE html><html lang=\"fr\">\n\t<body>\n";
    for(let i = 0; i < images.length;++i){
        const img = images[i];
        out_html += `\t\t<img src=\"${folderName}/${i}.png\" alt=\"${img.alt}\">\n`; 
        await page.goto(img.src, { waitUntil: 'networkidle2' });
        const imgHandle = await page.$('img');
        if(imgHandle){
            await imgHandle.screenshot({ path: `${folderName}/${i}.png` });
        }
    }
    out_html += "\t</body>\n</html>\n";
    
    fs.writeFileSync("content.html",out_html);
    // console.log(images);

    await browser.close();
}

scrapeInstagram();
