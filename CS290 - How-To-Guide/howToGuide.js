var express = require('express');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
//var credentials = require('./credentials.js');
//var request = require('request');
var sassMiddleware = require('node-sass-middleware')

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);

app.use(sassMiddleware({
    /* Options */
    root: __dirname + '/public/stylesheets',
    src: '/sass',
    dest:'/css',
    debug: true,
    outputStyle: 'compressed',
    prefix:'/stylesheets/css' // Where prefix is at <link rel="stylesheets" href="prefix/style.css"/>
}));

app.use(express.static('public'));

app.get('/',function(req,res){
  var pageClasses = [];
  pageClasses.home = "current_page_item";
  res.render('home', {showTitle: true, classes:pageClasses});
});

app.get('/introToSASS',function(req,res){
  var pageClasses = [];
  pageClasses.introToSASS = "current_page_item";
  res.render('introToSASS', {classes:pageClasses});
});

app.get('/theTwoSyntaxes',function(req,res){
  var pageClasses = [];
  pageClasses.theTwoSyntaxes = "current_page_item";
  res.render('theTwoSyntaxes', {classes:pageClasses});
});

app.get('/usingSASS',function(req,res){
  var pageClasses = [];
  pageClasses.usingSASS = "current_page_item";
  res.render('usingSASS', {classes:pageClasses});
});

app.get('/usingSASS-onTheCommandLine',function(req,res){
  var pageClasses = [];
  pageClasses.usingSASSonCL = "current_page_item";
  res.render('usingSASS-onTheCommandLine', {classes:pageClasses});
});

app.get('/usingSASS-withNodeJS',function(req,res){
  var pageClasses = [];
  pageClasses.usingSASSwNodeJS = "current_page_item";
  res.render('usingSASS-withNodeJS', {classes:pageClasses});
});

app.get('/wrapUp',function(req,res){
  var pageClasses = [];
  pageClasses.wrapUp = "current_page_item";
  res.render('wrapUp', {classes:pageClasses});
});


app.use(function(req,res){
  res.status(404);
  res.render('404', {layout:false});
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('500', {layout: false});
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});

