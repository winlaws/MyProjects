var express = require('express');
var app = express();
var bodyParser = require('body-parser');
app.use(bodyParser.json());

var mysql = require('mysql');
var pool = mysql.createPool({
  host  : 'localhost',
  user  : 'student',
  password: 'default',
  database: 'student'
});

app.set('port', 3001);

app.use(express.static('public'));

app.post('/table',function(req,res){
  pool.query('SELECT * FROM workouts', function(err, rows, fields){
    if(err){
      next(err);
      return;
    }
    res.send(rows);
  });
});

app.post('/add',function(req, res, next){
  pool.query("INSERT INTO workouts(`name`, `reps`, `weight`, `lbs`, `date`) VALUES (?, ?, ?, ?, ?)", [req.body.name, req.body.reps, req.body.weight, req.body.lbs, req.body.date], function(err, rows, fields){
    if(err){
      next(err);
      return;
    }
    pool.query('SELECT * FROM workouts WHERE id =?',[rows.insertId], function(err, rows, fields){
      if(err){
        next(err);
        return;
      }

      var added = rows[0];
      res.send(JSON.stringify(added));
    });
  });
});

app.post('/delete',function(req, res, next){
  pool.query('SELECT * FROM workouts WHERE id =?', [req.body.id], function(err, rows, fields){
    if(err){
      next(err);
      return;
    }
    var deleted = rows[0];
    pool.query("DELETE FROM workouts WHERE id=?", [req.body.id], function(err, rows, fields){
      if(err){
        next(err);
        return;
      }
      res.send(JSON.stringify(deleted));
    });
  });
});


app.post('/edit', function(req, res, next){
  pool.query("SELECT * FROM workouts WHERE id=?", [req.body.id], function(err, rows, fields){
    if(err){
      next(err);
      return;
    }
    if(rows.length == 1){
      pool.query("UPDATE workouts SET name=?, reps=?, weight=?, date=?, lbs=?  WHERE id=? ", 
        [req.body.name, req.body.reps, req.body.weight, req.body.date, req.body.lbs,  req.body.id],
        function(err, rows, fields){
          if(err){
            next(err);
            return;
          }
          pool.query("SELECT * FROM workouts WHERE id=?", [req.body.id], function(err, rows, fields){
            if(err){
              next(err);
              return;
            }
            
            var updated = rows[0];
            res.send(JSON.stringify(updated));
          });
        });
    }
  });
});

app.get('/reset-table',function(req, res, next){
  pool.query("DROP TABLE IF EXISTS workouts", function(err){ 
    var createString = "CREATE TABLE workouts("+
    "id INT PRIMARY KEY AUTO_INCREMENT,"+
    "name VARCHAR(255) NOT NULL,"+
    "reps INT,"+
    "weight INT,"+
    "date DATE,"+
    "lbs BOOLEAN)";
    pool.query(createString, function(err){
      res.send("Table Has Been Reset");
    })
  });
});

app.use(function(req,res){
  res.status(404);
  res.send("404 Error");
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.send("500 Error");
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});

