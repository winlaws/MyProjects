using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Net;
using System.Web.Mvc;
using SCPSInventory.DAL;
using SCPSInventory.Models;
using System.Data.Entity;

namespace SCPSInventory.Controllers
{
    public class InventoriesController : Controller
    {
        private SCPSInventoryContext db = new SCPSInventoryContext();

        // GET: Inventories/List/0021
        public ActionResult List(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            CostCenter costCenter = db.CostCenters.Find(id);
            if (costCenter == null)
            {
                return HttpNotFound();
            }
            costCenter.Inventories = db.Inventories.Where(inventory => inventory.ccId == id).ToList();
            foreach (Inventory inventory in costCenter.Inventories)
            {
                if (inventory.Status == InventoryStatus.InProgress)
                {
                    costCenter.AssetList = db.Assets.Where(asset => asset.ccId == costCenter.CostCenterId).ToList();
                    inventory.numAssetsToInventory = costCenter.AssetList.Count();
                    inventory.numAssetsInventoried = costCenter.AssetList.Count(asset => asset.InventoryDate >= inventory.InventoryStartDate);
                }
            }
            return View(costCenter);
        }

        // GET: Inventories/Create/0021
        public ActionResult Create(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }

            CostCenter costCenter = db.CostCenters.Find(id);
            if (costCenter == null)
            {
                return HttpNotFound();
            }
            costCenter.Inventories = db.Inventories.Where(inventory => inventory.ccId == id).ToList();
            if (costCenter.Inventories.Any(inventory => inventory.Status == InventoryStatus.InProgress))
            {
                foreach (Inventory inventory in costCenter.Inventories)
                {
                    if (inventory.Status == InventoryStatus.InProgress)
                    {
                        costCenter.AssetList = db.Assets.Where(asset => asset.ccId == costCenter.CostCenterId).ToList();
                        inventory.numAssetsToInventory = costCenter.AssetList.Count();
                        inventory.numAssetsInventoried = costCenter.AssetList.Count(asset => asset.InventoryDate >= inventory.InventoryStartDate);
                    }
                }
                return View("CannotCreate", costCenter);
            }

            if (db.Assets.Any(asset => asset.ccId == id))
            {
                Inventory newInventory = new Inventory();
                newInventory.ccId = id;
                newInventory.InventoryStartDate = DateTime.Now;
                newInventory.InventoryEndDate = DateTime.MinValue;
                newInventory.Status = InventoryStatus.InProgress;
                return View(newInventory);
            }

            return View("CannotCreateNoAssets", costCenter);
        }

        // POST: Inventories/Create/0021
        [HttpPost, ActionName("Create")]
        [ValidateAntiForgeryToken]
        public ActionResult CreateConfirmed(string id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Inventory inventory = new Inventory();
            inventory.ccId = id;
            inventory.InventoryStartDate = DateTime.Now;
            inventory.InventoryEndDate = DateTime.MaxValue;
            inventory.Status = InventoryStatus.InProgress;
            List<Asset> assets = db.Assets.Where(asset => asset.ccId == id).ToList();
            inventory.numAssetsToInventory = assets.Count();
            inventory.numAssetsInventoried = assets.Count(asset => asset.InventoryDate > inventory.InventoryStartDate);
            db.Inventories.Add(inventory);
            db.SaveChanges();
            return RedirectToAction("List", new { id = inventory.ccId });
        }

        // GET: Inventories/Close/5
        public ActionResult Close(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Inventory inventory = db.Inventories.Find(id);
            if (inventory == null)
            {
                return HttpNotFound();
            }
            return View(inventory);
        }

        // POST: Inventories/Close/5
        // To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        // more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost, ActionName("Close")]
        [ValidateAntiForgeryToken]
        public ActionResult CloseConfirm(int? id)
        {
            Inventory inventory = db.Inventories.Find(id);
            inventory.InventoryEndDate = DateTime.Now;
            inventory.numAssetsToInventory = db.Assets.Count(asset => asset.ccId == inventory.ccId);
            inventory.numAssetsInventoried = db.Assets.Count(asset => asset.InventoryDate >= inventory.InventoryStartDate && asset.InventoryDate <= inventory.InventoryEndDate);
            inventory.Status = InventoryStatus.Closed;
            db.Entry(inventory).State = EntityState.Modified;
            db.SaveChanges();
            return RedirectToAction("List", new { id = inventory.ccId });
        }

        // GET: Inventories/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Inventory inventory = db.Inventories.Find(id);
            if (inventory == null)
            {
                return HttpNotFound();
            }
            return View(inventory);
        }

        // POST: Inventories/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int? id)
        {
            Inventory inventory = db.Inventories.Find(id);
            db.Inventories.Remove(inventory);
            db.SaveChanges();
            return RedirectToAction("List", new { id = inventory.ccId } );
        }

        // GET: Inventories/Inventory/5
        public ActionResult Inventory(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Inventory inventory = db.Inventories.Find(id);
            if (inventory == null)
            {
                return HttpNotFound();
            }
            return View(inventory);
        }

        // POST: Inventories/Inventory/5
        [HttpPost]
        [ValidateAntiForgeryToken]
        public void Inventory([Bind(Include = "assetId, ccId, Building, Rooom")] Asset asset)
        {
            Asset inventoried = db.Assets.Find(asset.AssetId);
            if(inventoried != null)
            {
                inventoried.ccId = asset.ccId;
                inventoried.Room = asset.Room;
                inventoried.Building = asset.Building;
                inventoried.InventoryDate = DateTime.Now;
          
                db.Entry(inventoried).State = EntityState.Modified;
                db.SaveChanges();
            }
        }

        //// GET: Inventories
        //public ActionResult Index()
        //{
        //    return View(db.Inventories.ToList());
        //}

        //// GET: Inventories/Details/5
        //public ActionResult Details(int? id)
        //{
        //    if (id == null)
        //    {
        //        return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
        //    }
        //    Inventory inventory = db.Inventories.Find(id);
        //    if (inventory == null)
        //    {
        //        return HttpNotFound();
        //    }
        //    return View(inventory);
        //}

        //// GET: Inventories/Create
        //public ActionResult Create()
        //{
        //    return View();
        //}

        //// POST: Inventories/Create
        //// To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        //// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        //[HttpPost]
        //[ValidateAntiForgeryToken]
        //public ActionResult Create([Bind(Include = "InventoryId,ccId,InventoryStartDate,InventoryEndDate,Status,numAssetsToInventory,numAssetsInventoried")] Inventory inventory)
        //{
        //    if (ModelState.IsValid)
        //    {
        //        db.Inventories.Add(inventory);
        //        db.SaveChanges();
        //        return RedirectToAction("Index");
        //    }

        //    return View(inventory);
        //}

        //// GET: Inventories/Edit/5
        //public ActionResult Edit(int? id)
        //{
        //    if (id == null)
        //    {
        //        return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
        //    }
        //    Inventory inventory = db.Inventories.Find(id);
        //    if (inventory == null)
        //    {
        //        return HttpNotFound();
        //    }
        //    return View(inventory);
        //}

        //// POST: Inventories/Edit/5
        //// To protect from overposting attacks, please enable the specific properties you want to bind to, for 
        //// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
        //[HttpPost]
        //[ValidateAntiForgeryToken]
        //public ActionResult Edit([Bind(Include = "InventoryId,ccId,InventoryStartDate,InventoryEndDate,Status,numAssetsToInventory,numAssetsInventoried")] Inventory inventory)
        //{
        //    if (ModelState.IsValid)
        //    {
        //        db.Entry(inventory).State = EntityState.Modified;
        //        db.SaveChanges();
        //        return RedirectToAction("Index");
        //    }
        //    return View(inventory);
        //}

        //// GET: Inventories/Delete/5
        //public ActionResult Delete(int? id)
        //{
        //    if (id == null)
        //    {
        //        return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
        //    }
        //    Inventory inventory = db.Inventories.Find(id);
        //    if (inventory == null)
        //    {
        //        return HttpNotFound();
        //    }
        //    return View(inventory);
        //}

        //// POST: Inventories/Delete/5
        //[HttpPost, ActionName("Delete")]
        //[ValidateAntiForgeryToken]
        //public ActionResult DeleteConfirmed(int id)
        //{
        //    Inventory inventory = db.Inventories.Find(id);
        //    db.Inventories.Remove(inventory);
        //    db.SaveChanges();
        //    return RedirectToAction("Index");
        //}

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }
    }
}
